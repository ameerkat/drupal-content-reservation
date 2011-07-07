<?php if($content_list): ?>
<div id="content_reservation_list-wrapper" class="content_reservation">
<table><tr><td>
<div id="content_reservation-fullCalendar"></div>
</div>
</td><td width="400">
<ul id="content_reservation_list" class="content_reservation">
<?php foreach($content_list as $event): ?>
	<li>
	<a href="<?php echo $event->reservation_url; ?>"><?php echo $event->description; ?></a><br />
	<?php echo $event->start; ?> : <?php echo $event->end; ?><br />
	<a href="<?php echo $event->approve_url; ?>"><img src="<?php echo $event->approve_image; ?>" /> approve</a>
	<a href="<?php echo $event->reject_url; ?>"><img src="<?php echo $event->reject_image; ?>" /> reject</a>
	</li>
<?php endforeach; ?>
</ul></td></tr></table>
<?php else: ?>
<h2>Event List Empty</h2>
<?php endif; ?>
