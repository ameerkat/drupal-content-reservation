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

function content_reservation_admin(){
	$form = array();
	$form['content_reservation_showpast'] = array(
		'#type' => 'checkbox',
		'#title' => t('Show Past Events'),
		'#description' => t('Show events that have already past (when enabled will load ALL events ever created which make take a long time)'),
		'#default_value' => variable_get('content_reservation_showpast', 0));
	$form['content_reservation_reservepast'] = array(
		'#type' => 'checkbox',
		'#title' => t('Allow Reservation on Past Dates'),
		'#description' => t('Allow users to reserve on dates that have already passed'),
		'#default_value' => variable_get('content_reservation_reservepast', 0));
	$form['content_reservation_sendmodmail'] = array(
		'#type' => 'checkbox',
		'#title' => t('Send Email on Moderator Approve/Reject'),
		'#description' => t('Sends an email to the user with notification of reservation status'),
		'#default_value' => variable_get('content_reservation_sendmodmail', 1));
	$form['content_reservation_showuser'] = array(
		'#type' => 'checkbox',
		'#title' => t('Show Usernames on Calendar'),
		'#description' => t('Append the user name to the calendar view information'),
		'#default_value' => variable_get('content_reservation_showuser', 1));
	$form['content_reservation_hidesinglelanding'] = array(
		'#type' => 'checkbox',
		'#title' => t('Hide the Landing Page for Single Reservable Contents'),
		'#description' => t('Hide the landing page if only one content type has reservations, will default to that type'),
		'#default_value' => variable_get('content_reservation_hidesinglelanding', 1));
	return system_settings_form($form);
}

