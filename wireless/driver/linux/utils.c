/******************************************************************************

                               Copyright (c) 2012
                            Lantiq Deutschland GmbH

  For licensing information, see the file 'LICENSE' in the root folder of
  this software module.

******************************************************************************/
/*
 * $Id$
 *
 * 
 *
 * Utilities.
 *
 * Originally written by Andrey Fidrya
 *
 */
#include "mtlkinc.h"

#include "utils.h"

#define LOG_LOCAL_GID   GID_UTILS
#define LOG_LOCAL_FID   1

/*
 * Function outputs buffer in hex format
 */
#ifdef MTCFG_SILENT
void __MTLK_IFUNC
mtlk_aux_print_hex (const void *buf, unsigned int l)
{
}
#else

#ifdef MTCFG_SILENT
#define LOG_BUFFER
#else
#define LOG_BUFFER             pr_cont
#endif

void __MTLK_IFUNC
mtlk_aux_print_hex (const void *buf, unsigned int l)
{
  unsigned int i,j;
  unsigned char *cp = (unsigned char*)buf;

//TODO should be probably locked

  LOG_BUFFER("cp= 0x%p l=%d\n", cp, l);
  for (i = 0; i < l/16; i++) {
    LOG_BUFFER("%04x:  ", 16*i);
    for (j = 0; j < 16; j++)
      LOG_BUFFER("%02x %s", *cp++, j== 7 ? " " : "");
    LOG_BUFFER("\n");
  }
  if (l & 0x0f) {
    LOG_BUFFER("%04x:  ", 16*i);
    for (j = 0; j < (l&0x0f); j++)
      LOG_BUFFER("%02x %s", *cp++, j== 7 ? " " : "");
    LOG_BUFFER("\n");
  }
}
#endif

void __mtlk_dump(const void *buf, uint32 len, char *str)
{
  ILOG0_S("%s",str);
  mtlk_aux_print_hex(buf, len);
}

uint32
mtlk_shexdump (char *buffer, uint8 *data, size_t size)
{
  uint8 line, i;
  uint32 counter = 0;

  for (line = 0; size; line++) {
    counter += sprintf(buffer+counter, "%04x: ", line * 0x10);
    for (i = 0x10; i && size; size--,i--,data++) {
      counter +=sprintf(buffer+counter, " %02x", *data);
    }
    counter += sprintf(buffer+counter, "\n");
  }
  return counter;
}

char * __MTLK_IFUNC
mtlk_get_token (char *str, char *buf, size_t len, char delim)
{
  char *dlm;

  if (!str) {
    buf[0] = 0;
    return NULL;
  }
  dlm = strchr(str, delim);
  if (dlm && ((size_t)(dlm - str) < len)) {
    memcpy(buf, str, dlm - str);
    buf[dlm - str] = 0;
  } else {
    memcpy(buf, str, len - 1);
    buf[len - 1] = 0;
  }
  ILOG4_S("Get token: '%s'", buf);
  if (dlm)
    return dlm + 1;
  return dlm;
}

/*
  Extract MAC address from string

  \param str   - string with MAC address [I]
  \param addr  - pointer to MAC storage [O]

  \return
     MTLK_ERR_PARAMS - wrong format of MAC address in the string
     MTLK_ERR_OK - success

  \remark
     accepted the following string formats
       XX:XX:XX:XX:XX:XX
*/
int __MTLK_IFUNC
mtlk_str_to_mac (char const *str, uint8 *addr)
{
  int i;

  MTLK_ASSERT(NULL != str);
  MTLK_ASSERT(NULL != addr);

  str = mtlk_str_ltrim(str);

  if (strlen(str) < 17)
    return MTLK_ERR_PARAMS;

  if ((':' != str[2]) ||
      (':' != str[5]) ||
      (':' != str[8]) ||
      (':' != str[11]) ||
      (':' != str[14]))
    return MTLK_ERR_PARAMS;

  memset (addr, 0, sizeof(*addr));

  for (i = 0; i < 6; i++)
  {
    addr[i] = mtlk_str_x2tol(str + (i * 3));
  }

  return MTLK_ERR_OK;
}
