<?php
/*
 * Copyright 2011 Ameer Ayoub
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

function content_reservation_moderate($mode = "type", $key = NULL, $action = NULL){
	global $user, $base_url;
	$module_path = drupal_get_path('module', 'content_reservation');
	drupal_add_css($module_path.'/content-reservation.css');
	drupal_add_js($module_path.'/lib/fullcalendar/jquery/'.variable_get("fc_jquery_filename", update_fc_jquery_fname()));
	drupal_add_css($module_path.'/lib/fullcalendar/fullcalendar/fullcalendar.css');
	drupal_add_js($module_path.'/lib/fullcalendar/fullcalendar/fullcalendar.js');
	jquery_ui_add('ui.resizable');
	if($mode == "type" ){
		$content_type = $key;
		if($content_type){
			$content_list = array();
			// 1 is the status code for published
			$result = db_query("SELECT * FROM {content_reservation}, {users} WHERE {users}.uid = {content_reservation}.uid AND {content_reservation}.status = %d",  ContentReservation::$CODE_CREATED);
			while ($row = db_fetch_object($result)) {
				// @todo All this stuff should be moved to the theme preprocessor callback
				$row->content_name = get_readable_content_title($row->nid);
				$row->content_url = $base_url."/reservations/r/id/".$row->nid;
				$row->content_url_color = content_reservation_get_color_var($row->nid);
				$row->content_url_textColor = content_reservation_get_textColor_var($row->nid);
				$row->reservation_url = $base_url."/reservations/r/edit/".$row->rid;
				$row->approve_url = $base_url."/reservations/m/id/".$row->rid."/approve";
				$row->reject_url = $base_url."/reservations/m/id/".$row->rid."/reject";
				$row->user_url = $base_url."/user/".$row->uid;
				$usable_time = convert_iso8601_time($row->start);
				$row->show_js = "javascript:$('#content_reservation-fullCalendar').fullCalendar('gotoDate', $.fullCalendar.parseDate('$usable_time'));";
				$row->show_image = $base_url.'/'.$module_path.'/images/calendar.png';
				$row->edit_image = $base_url.'/'.$module_path.'/images/calendar_edit.png';
				$row->approve_image = $base_url.'/'.$module_path.'/images/accept.png';
				$row->reject_image = $base_url.'/'.$module_path.'/images/reject.png';
				$row->user_image = $base_url.'/'.$module_path.'/images/user.png';
				$content_list[] = $row;
			}
			if(!empty($content_list)){
				$content_name = get_readable_content_type($content_type);
				if($content_name){
					drupal_set_title("Unapproved ".$content_name." Reservations");
				}
				$event_list_json = content_reservation_json("type", $content_type, false);
				drupal_add_js(theme("content_reservation_fullcalendar_js", $event_list_json), 'inline');
				return theme("content_reservation_moderate", $content_list);
			} else {
				drupal_set_message("No unapproved content for this content type found",
					"warning");
				return "";
			}
		} else {
			drupal_set_message("No content type specified", "warning");
			return "";
		}
	} else if ($mode == "id") {
		$content_id = $key;
		if($content_id){
			if($action == "approve") {
				db_query("UPDATE {content_reservation} SET status=%d WHERE rid=%d", 
					ContentReservation::$CODE_APPROVED, $content_id);
				drupal_set_message("Event $content_id has been approved. {status: ".ContentReservation::$CODE_APPROVED."}");
				return "";
			} else if ($action == "reject") {
				db_query("UPDATE {content_reservation} SET status=%d WHERE rid=%d", 
					ContentReservation::$CODE_REJECTED, $content_id);
				drupal_set_message("Event $content_id has been rejected. {status: ".ContentReservation::$CODE_REJECTED."}");
				return "";
			} else {
				drupal_set_message("Invalid event action, must be one of {approve, reject}", 'error');
				return "";
			}
		}
	} else {
		drupal_set_message("Invalid query mode $mode, must be one of type, id", 'error');
		return "";
	}
}
