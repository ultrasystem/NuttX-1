/****************************************************************************
 * graphics/nxtk/nxtk_filltoolbar.c
 *
 *   Copyright (C) 2008 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <spudmonkey@racsa.co.cr>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/nx.h>
#include <nuttx/nxtk.h>

#include "nxfe.h"
#include "nxtk_internal.h"

/****************************************************************************
 * Pre-Processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: nxtk_filltoolbar
 *
 * Description:
 *  Fill the specified rectangle in the client window with the specified color
 *
 * Input Parameters:
 *   htb  -  The toolbar handle returned by nxtk_opentoolbar
 *   rect  - The location within the toolbar window to be filled
 *   color - The color to use in the fill
 *
 * Return:
 *   OK on success; ERROR on failure with errno set appropriately
 *
 ****************************************************************************/

int nxtk_filltoolbar(NXTKTOOLBAR htb, FAR const struct nxgl_rect_s *rect,
                     nxgl_mxpixel_t color[CONFIG_NX_NPLANES])
{
  FAR struct nxtk_framedwindow_s *fwnd = (FAR struct nxtk_framedwindow_s *)htb;
  struct nxgl_rect_s  relbounds;
  struct nxgl_rect_s cliprect;

#ifdef CONFIG_DEBUG
  if (!htb || !rect || !color)
    {
      errno = EINVAL;
      return ERROR;
    }
#endif

  /* Clip the rectangle to lie within the toolbar region */

  nxgl_rectoffset(&relbounds, &fwnd->tbrect, fwnd->tbrect.pt1.x, fwnd->tbrect.pt1.y);
  nxgl_rectintersect(&cliprect, rect, &relbounds);

  /* Then fill it */

  return nx_fill((NXWINDOW)htb, &cliprect, color);
}
