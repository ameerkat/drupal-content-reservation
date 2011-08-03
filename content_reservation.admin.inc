<?php
function content_reservation_admin(){
	$form = array();
	$form['content_reservation_showpast'] = array(
		'type' => 'checkbox',
		'#title' => t('Show Past Events');
		'#description' => 'Show events that have already past (when enabled will load ALL events ever created which make take a long time)';
		'#default_value' => variable_get('content_reservation_showpast', 0));
	return system_settings_form($form);
}
