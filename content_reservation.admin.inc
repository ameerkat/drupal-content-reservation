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
		'#default_value' => variable_get('content_reservation_showpast', 0),
	);
	$form['content_reservation_reservepast'] = array(
		'#type' => 'checkbox'
		'#title' => t('Allow Reservation on Past Dates'),
		'#description' => t('Allow users to reserve on dates that have already passed'),
		'#default_value' => variable_get('content_reservation_reservepast', 0),
	);
	return system_settings_form($form);
}

