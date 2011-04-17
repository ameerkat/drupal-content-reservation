$(document).ready(function() {
	$('#content_reservation-fullCalendar').fullCalendar({
		header: {
				left: 'prev,next today',
				center: 'title',
				right: 'month,agendaWeek,agendaDay'
		},
		events: <?php echo($event_list); ?>
	});
});
