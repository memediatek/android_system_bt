/******************************************************************************
 *
 *  Copyright (C) 1999-2012 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

/******************************************************************************
 *
 *  this file contains functions that handle the pbap sdp switch for v1.1,v1.2
 *
 ******************************************************************************/
#if defined(MTK_INTEROP_EXTENSION) && (MTK_INTEROP_EXTENSION == TRUE)

#include "bt_trace.h"
#include "include/hardware/bt_sdp.h"
#include "interop_mtk.h"
#include "mtk_sdp_pbap.h"
#include "bta_sdp_api.h"
#include "osi/include/osi.h"

int pbap_sdp_v11_handle = -1;
int pbap_sdp_v12_handle = -1;
int *current_sdp_version_handle = &pbap_sdp_v12_handle;

extern bt_status_t create_sdp_record(bluetooth_sdp_record* record,
                              int* record_handle);
extern void on_create_record_event(int id);
extern void on_remove_record_event(int handle);

extern int get_sdp_handle(int id);

bt_status_t mtk_remove_pbap_sdp_from_db(int handle) {

  int sdp_handle = get_sdp_handle(handle);
  BTIF_TRACE_WARNING("%s - id is %d,sdp_handle=%x",__func__,handle,sdp_handle);
  if(sdp_handle <= 0){
    BTIF_TRACE_WARNING("%s - sdp_handle is 0",__func__);
    return BT_STATUS_FAIL;
  }
  on_remove_record_event(sdp_handle);
  return BT_STATUS_SUCCESS;
}

void mtk_save_pbap_handle(int handle, bool v11) {

  BTIF_TRACE_WARNING("%s - handle=%d, is v1.1=%d",__func__,handle,v11);
  if (v11) {
    if(pbap_sdp_v11_handle < 0) {
      //the first pbap v1.1 add, we need remove it
      mtk_remove_pbap_sdp_from_db(handle);
      pbap_sdp_v11_handle = handle;
    }
  }
  else {
    if (pbap_sdp_v12_handle < 0)
      pbap_sdp_v12_handle = handle;
  }

}

bt_status_t mtk_add_pbap_sdp_from_db(int handle) {

  BTIF_TRACE_WARNING("%s - handle id is %d",__func__,handle);
  if(handle < 0){
    return BT_STATUS_FAIL;
  }
  on_create_record_event(handle);
  return BT_STATUS_SUCCESS;
}

bt_status_t mtk_create_sdp_recored_v11() {

  int id = -1;
  bluetooth_sdp_record record = {};
  record.pse.hdr.type = SDP_TYPE_PBAP_PSE;
  const char* service_name = "OBEX Phonebook Access Server";
  record.pse.hdr.service_name = (char*)service_name;
  record.pse.hdr.service_name_length = strlen(service_name);
  record.pse.hdr.rfcomm_channel_number = 19;
  record.pse.hdr.l2cap_psm = -1;
  record.pse.hdr.profile_version = 0x0101;
  record.pse.supported_features = 0x0001;
  record.pse.supported_repositories = 0x0001;
  if (pbap_sdp_v11_handle >= 0) {
    BTIF_TRACE_WARNING("%s - pbap 1.1 is create yeat handle=%d",__func__,pbap_sdp_v11_handle);
    return BT_STATUS_SUCCESS;
  }

  return create_sdp_record(&record,&id);
}

static bt_status_t mtk_set_pbap_sdp_to(bool v_11) {

  BTIF_TRACE_WARNING("%s - set version to v%s",__func__, v_11 ? "1.1":"1.2");
  int* new_handle = v_11 ? &pbap_sdp_v11_handle:&pbap_sdp_v12_handle;
  if (new_handle != current_sdp_version_handle) {
    mtk_remove_pbap_sdp_from_db(*current_sdp_version_handle);
    mtk_add_pbap_sdp_from_db(*new_handle);
    current_sdp_version_handle = new_handle;
  }
  return BT_STATUS_SUCCESS;
}

void mtk_check_pbap_version(RawAddress& addr) {

  bool v_11 = false;
  if (interop_mtk_match_addr_name(INTEROP_MTK_SDP_PBAP_1_1, &addr)) {
      BTIF_TRACE_WARNING("Downgrade pbap version for IOT device");
      v_11 = true;
  }
  mtk_set_pbap_sdp_to(v_11);

}

#endif

