/*****************************************************************************
#                                                                            #
#    uStreamer - Lightweight and fast MJPG-HTTP streamer.                    #
#                                                                            #
#    Copyright (C) 2018  Maxim Devaev <mdevaev@gmail.com>                    #
#                                                                            #
#    This program is free software: you can redistribute it and/or modify    #
#    it under the terms of the GNU General Public License as published by    #
#    the Free Software Foundation, either version 3 of the License, or       #
#    (at your option) any later version.                                     #
#                                                                            #
#    This program is distributed in the hope that it will be useful,         #
#    but WITHOUT ANY WARRANTY; without even the implied warranty of          #
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           #
#    GNU General Public License for more details.                            #
#                                                                            #
#    You should have received a copy of the GNU General Public License       #
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.  #
#                                                                            #
*****************************************************************************/


#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include <linux/videodev2.h>

#include <bcm_host.h>
#include <IL/OMX_Core.h>
#include <IL/OMX_Component.h>
#include <IL/OMX_Broadcom.h>
#include <interface/vcos/vcos_semaphore.h>

#include "../../../common/logging.h"
#include "../../../common/tools.h"
#include "../../device.h"
#include "../../frame.h"

#include "formatters.h"
#include "component.h"


#ifndef CFG_OMX_MAX_ENCODERS
#	define CFG_OMX_MAX_ENCODERS 3 // Raspberry Pi limitation
#endif
#define OMX_MAX_ENCODERS ((unsigned)(CFG_OMX_MAX_ENCODERS))


struct omx_encoder_t {
	OMX_HANDLETYPE			encoder;
	OMX_BUFFERHEADERTYPE	*input_buffer;
	OMX_BUFFERHEADERTYPE	*output_buffer;
	bool					input_required;
	bool					output_available;
	bool					failed;
	VCOS_SEMAPHORE_T		handler_sem;

	bool	i_handler_sem;
	bool	i_encoder;
	bool	i_input_port_enabled;
	bool	i_output_port_enabled;
};


struct omx_encoder_t *omx_encoder_init(void);
void omx_encoder_destroy(struct omx_encoder_t *omx);

int omx_encoder_prepare(struct omx_encoder_t *omx, struct device_t *dev, unsigned quality);
int omx_encoder_compress_buffer(struct omx_encoder_t *omx, struct hw_buffer_t *hw, struct frame_t *frame);
