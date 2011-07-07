$(document).ready(function() {
	$('#content_reservation-fullCalendar').fullCalendar({
		header: {
				left: 'prev,next today',
				center: 'title',
				right: 'month,agendaWeek,agendaDay'
		},
		events: <?php echo($event_list); ?>
	});
	
	$("#content_reservation-fullCalendar").resizable({
		handles: 'e',
		create:
			function(event, ui){
				$('#content_reservation-fullCalendar').fullCalendar("render");
				console.log("fullCalendar resize intialized");
			},
		resize:
			function(event, ui) {
				$('#content_reservation-fullCalendar').fullCalendar("render");
				console.log("fullCalendar resize callback triggered");
			}
	});
	
	/*
	$("#content_reservation-fullCalendar").bind("resize", function(event, ui) {
		$('#content_reservation-fullCalendar').fullCalendar("render");
	});
	*/
});
