/* Copyright Statement:
 * *
 * * This software/firmware and related documentation ("MediaTek Software") are
 * * protected under relevant copyright laws. The information contained herein
 * * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * * Without the prior written permission of MediaTek inc. and/or its licensors,
 * * any reproduction, modification, use or disclosure of MediaTek Software,
 * * and information contained herein, in whole or in part, shall be strictly prohibited.
 * *
 * * MediaTek Inc. (C) 2016. All rights reserved.
 * *
 * * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 * *
 * * The following software/firmware and/or related documentation ("MediaTek Software")
 * * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * * applicable license agreements with MediaTek Inc.
 * */


#pragma once

#include "bt_types.h"
#include "raw_address.h"

#if defined(MTK_INTEROP_EXTENSION) && (MTK_INTEROP_EXTENSION == TRUE)

/*******************************************************************************
**
** Function     mtk_create_sdp_recored_v11
**
** Description  This function is create a pbap 1.1 sdp recored
**
** Returns      success or fail
**
*******************************************************************************/
extern bt_status_t mtk_create_sdp_recored_v11();
/*******************************************************************************
**
** Function     mtk_remove_pbap_sdp_from_db
**
** Description  This function is remove pbap sdp recored from sdp service db
**
** Returns      void
**
*******************************************************************************/
extern bt_status_t mtk_remove_pbap_sdp_from_db(int handle);
/*******************************************************************************
**
** Function     mtk_check_pbap_version
**
** Description  This function is check the addr in PBAP1.1 blacklist, if in then
** remove the pbap1.2 sdp recored from sdp server and add pbap 1.1 in, other, 
** remove the pbap1.1 and add the pbap1.2
**
** Returns      success or fail
**
*******************************************************************************/
extern void mtk_check_pbap_version(RawAddress& addr);
/*******************************************************************************
**
** Function     mtk_save_pbap_handle
**
** Description  This function is save the sdp record id when sdp recored create
** successfully.
**
** Returns      success or fail
**
*******************************************************************************/
extern void mtk_save_pbap_handle(int handle, bool v11);
#else
//if not define the blacklist feature, do nothing
#define mtk_create_sdp_recored_v11() (0)
#define mtk_remove_pbap_sdp_from_db(handle) (0)
#define mtk_check_pbap_version(addr)
#define mtk_save_pbap_handle(handle,v11)

#endif
