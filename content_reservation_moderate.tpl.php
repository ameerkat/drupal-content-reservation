<?php if($content_list): ?>
<div id="content_reservation_list-wrapper" class="content_reservation">
<table><tr><td>
<div id="content_reservation-fullCalendar"></div>
</div>
</td><td id="content_reservation_list_td" class="moderate">
<ul id="content_reservation_list" class="content_reservation">
<?php foreach($content_list as $event): ?>
	<li class="moderate">
	<img src="<?php echo $event->show_image; ?>" alt="Show on Calendar" onclick="<?php echo $event->show_js; ?>" style="cursor: pointer;"/>
	<a href="<?php echo $event->reservation_url; ?>"><?php echo $event->description; ?></a><br />
	<a href="<?php echo $event->user_url; ?>"><img src="<?php echo $event->user_image; ?>" /> <?php echo $event->name; ?></a><br />
	<span class="time-range" style="font-size: 8pt;"><?php echo $event->start; ?> to<br /> <?php echo $event->end; ?></span><br />
	<a href="<?php echo $event->approve_url; ?>"><img src="<?php echo $event->approve_image; ?>" /> approve</a>
	<a href="<?php echo $event->reject_url; ?>"><img src="<?php echo $event->reject_image; ?>" /> reject</a>
	</li>
<?php endforeach; ?>
</ul></td></tr></table>
<?php else: ?>
<h2>Event List Empty</h2>
<?php endif; ?>
