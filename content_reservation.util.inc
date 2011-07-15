<?php
/**
 * Get human readable node type name from machine readable name.
 * @param string $machine_type_name machine readable name of content type
 * @return string
 */
function get_readable_content_type($machine_type_name){
	$result = db_query("SELECT name FROM {node_type} WHERE type = '%s'",  
		$machine_type_name);
	$row = db_fetch_object($result);
	if($row){
		return $row->name;
	} else {
		return NULL;
	}
}

/**
 * Get the content title based on the node id
 * @param integer $nid the node id of the node to get the title of
 */
function get_readable_content_title($nid){
	$result = db_query(
		"SELECT title FROM {node} WHERE nid = %d ORDER BY vid DESC",
		$nid);
	$row = db_fetch_object($result);
	if($row){
		return $row->title;
	} else {
		return NULL;
	}
}

/**
 * Returns the proper div container for the calendar display.
 * @return string
 */
function generate_calendar_div(){
	return "<div id=\"content_reservation-fullCalendar\"></div>";
}

/**
 * Returns a string containing an html formatted link to reservation for
 * a specific content type.
 * @param string $content_type machine readable content type
 * @return string
 */
function render_content_link($content_type){
	return "<a href=\"".content_reservation_get_content_link($content_type)
		."\">Back to $content_type</a>";
}

/**
 * Generate a plain text url to the reservation page for a specific content
 * type.
 * @param string $content_type machine readable content type
 * @return string
 */
function content_reservation_get_content_link($content_type){
	global $base_url;
	$readable = get_readable_content_type($content_type);
	return $base_url."/reservations/r/type/".$content_type;
}

/**
 * Converts the unix timestamp based on an input date time string in the
 * format of yyyy-mm-dd hh:mm:ss
 * @param string $datetime The formatted date time
 * @return integer
 */
function convert_unix_time($datetime){
	$pattern = '/(\d{4})-(\d{2})-(\d{2})\s*(\d{2}):(\d{2}):(\d{2})/';
	if (preg_match($pattern, $datetime, $matches) > 0){
		$year = $matches[1];
		$month = $matches[2];
		$day = $matches[3];
		$hour = $matches[4];
		$minute = $matches[5];
		$second = $matches[6];
		return mktime($hour, $minute, $second, $month, $day, $year);
	} else {
		drupal_set_message(
			"Incorrect date time format, date time must be in the format ".
			"yyyy-mmm-dd hh:mm:ss", "error");
		return 0;
	}
}

/**
 * Converts the input mysql date time into an ISO 8601 date time for use with
 * fullcalender jquery plugin.
 * format of in yyyy-mm-dd hh:mm:ss
 * @param string $datetime The formatted date time
 * @return integer
 */
function convert_iso8601_time($datetime){
	/*$pattern = '/(\d{4})-(\d{2})-(\d{2})\s*(\d{2}):(\d{2}):(\d{2})/';
	if (preg_match($pattern, $datetime, $matches) > 0){
		$year = $matches[1];
		$month = $matches[2];
		$day = $matches[3];
		$hour = $matches[4];
		$minute = $matches[5];
		$second = $matches[6];
		return $year."-".$month."-".$day."T".$hour.":".$minute.":".$second;*/
	$nt = str_replace(" ", "T", $datetime, $rc);
	if ($rc > 0){
		return $nt;
	} else {
		drupal_set_message(
			"convert_iso8601_time: Incorrect date time format, date time must be in the format ".
			"yyyy-mmm-dd hh:mm:ss", "error");
		return 0;
	}
}

/**
 * Whether the current logged in user has permissions to edit the reservation
 * @param integer $id Either ther user id or the reservation id of the 
 * 	reservation being checked for edit permission.
 * @param string $mode Either rid or uid as to what the $id represents with
 * 	respect to the reservation. defaults to rid.
 * @return boolean
 * @global user Uses the global user object of the current logged in user
 */
function check_reservation_edit_permissions($id, $mode = "rid"){
	global $user;
	if($mode == "rid"){
		if(user_access("modify reservations", $user)){
			return true;
		} else {
			$result = db_query(
				"SELECT rid, uid FROM {content_reservation} WHERE rid = %d",
				$rid);
			$row = db_fetch_object($result);
			if($row){
				if ($row->uid == $user.$rid){
					return true;
				}
			}
			return false;
		}
	} else if ($mode == "uid"){
		if(user_access("modify reservations", $user)){
			return true;
		} else if($user->uid == $uid) {
			return true;
		} else {
			return false;
		}
	} else {
		// Error: Invalid Mode
		drupal_set_message(
			"Invalid edit_permissions mode; must be one of uid or rid",
			"error");
		return false;
	}
}

/**
 * Generates a json array of serialized FullcalendarEvent objects
 * @param DatabaseStatementInterface $result The db_query return value to a
 *	query on the reservations db table.
 * @return string
 */
function content_reservation_make_json($result){
	$event_list = Array();
	while ($row = db_fetch_object($result)) {
		$event = new FullcalendarEvent();
		$event->id = $row->rid;
		$event->title = $row->description;
		// Convert times to fullcalendar compatible unix timestamp
		$event->start = convert_iso8601_time($row->start);
		$event->end = convert_iso8601_time($row->end);
		$event->color = content_reservation_get_color_var($row->nid);
		$event->textColor = content_reservation_get_textColor_var($row->nid);
		$event->allDay = false;
		if(check_reservation_edit_permissions($row->uid, "uid")){
			global $base_url;
			$event->url = $base_url."/reservations/r/edit/".$row->rid;
		}
		$event_list[] = $event;
	}
	return json_encode($event_list);
}

/**
 * Returns reservation events as serialized json FullCalender event object 
 * arrays based on various search queries.
 * @param string $query_type The type of query to be executed one of
 * `{type, nid, uid}. For querying on the content type, associated content node,
 * 	or associated user respectively.
 * @param string|integer $query_key The query key, either a string if type or
 *	a integer id nid or uid.
 * @return string
 */
function content_reservation_json($query_type, $query_key, $approved = true){
	if($approved){
		if ($query_type == 'type'){
			$result = db_query("SELECT * FROM {content_reservation}, {node} WHERE {node}.nid = {content_reservation}.nid AND {node}.type = '%s' AND {content_reservation}.status = %d",
			  $query_key, ContentReservation::$CODE_APPROVED);
			return content_reservation_make_json($result);
		} else if ($query_type == 'nid'){
			$result = db_query("SELECT * FROM {content_reservation} WHERE nid = %d AND {content_reservation}.status = %d",  $query_key, ContentReservation::$CODE_APPROVED);
			return content_reservation_make_json($result);
		} else if ($query_type == 'uid'){
			$result = db_query("SELECT * FROM {content_reservation} WHERE uid = %d AND {content_reservation}.status = %d",  $query_key, ContentReservation::$CODE_APPROVED);
			return content_reservation_make_json($result);
		} else {
			// If invalid query then return empty array
			return "[]";
		}
	} else {
		if ($query_type == 'type'){
			$result = db_query("SELECT * FROM {content_reservation}, {node} WHERE {node}.nid = {content_reservation}.nid AND {node}.type = '%s' AND {content_reservation}.status = %d",
			  $query_key, ContentReservation::$CODE_CREATED);
			return content_reservation_make_json($result);
		} else if ($query_type == 'nid'){
			$result = db_query("SELECT * FROM {content_reservation} WHERE nid = %d AND {content_reservation}.status = %d",  $query_key, ContentReservation::$CODE_CREATED);
			return content_reservation_make_json($result);
		} else if ($query_type == 'uid'){
			$result = db_query("SELECT * FROM {content_reservation} WHERE uid = %d AND {content_reservation}.status = %d",  $query_key, ContentReservation::$CODE_CREATED);
			return content_reservation_make_json($result);
		} else {
			// If invalid query then return empty array
			return "[]";
		}
	}
}

/**
 * Some helper function for getting and setting content calendar colors, and date
 *	format, all content specific variables.
 */
function content_reservation_get_color_var($nid){
	$var_name = "nid_". $nid . "_color";
	return variable_get($var_name, ContentReservation::$default_color);
}

function content_reservation_set_color_var($nid, $color){
	$var_name = "nid_". $nid . "_color";
	return variable_set($var_name, $color);
}

function content_reservation_set_dateFormat_var($nid, $dateFormat){
	$var_name = "nid_". $nid . "_dateFormat";
	return variable_set($var_name, $dateFormat);
}

function content_reservation_get_dateFormat_var($nid){
	$var_name = "nid_". $nid . "_dateFormat";
	return variable_get($var_name, ContentReservation::$default_dateFormat);
}

function content_reservation_get_dateIncrement_var($nid){
	$var_name = "nid_".$nid."_dateIncrement";
	return variable_get($var_name, ContentReservation::$default_dateIncrement);
}

function content_reservation_set_dateIncrement_var($nid, $dateIncrement){
	$var_name = "nid_". $nid . "_dateIncrement";
	return variable_set($var_name, $dateIncrement);
}

function content_reservation_get_textColor_var($nid){
	$var_name = "nid_". $nid . "_textColor";
	return variable_get($var_name, ContentReservation::$default_textColor);
}

function content_reservation_set_textColor_var($nid, $color){
	$var_name = "nid_". $nid . "_textColor";
	return variable_set($var_name, $color);
}

/**
 * Searches for the appropriate jquery filename that came packaged with fullcalendar
 */
function update_fc_jquery_fname(){
	$path = drupal_get_path('module', 'content_reservation') 
		. "/lib/fullcalendar/jquery";
	$pattern = "/^jquery-\d+.*\.js/";
	foreach(scandir($path) as $file){
		if (preg_match($pattern, $file, $matches)){
			variable_set("fc_jquery_filename", $file);
			return $file;
		}
	}
	return -1;
}

function get_nid_from_rid($reservation_id){
	$result = db_query(
		"SELECT rid, nid FROM {content_reservation} WHERE rid = %d",
		$reservation_id);
	$row = db_fetch_object($result);
	if($row){
		return $row->nid;
	} else {
		return NULL;
	}
}

function get_type_from_nid($nid){
	$result = db_query("SELECT nid, type FROM {node} WHERE nid = %d",  $nid);
	$row = db_fetch_object($result);
	if($row){
		return $row->type;
	} else {
		return NULL;
	}
}

