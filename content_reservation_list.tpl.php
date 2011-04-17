<?php if($content_list): ?>
<div id="content_reservation_list-wrapper" class="content_reservation">
<ul id="content_reservation_list" class="content_reservation">
<?php foreach($content_list as $reservable_content): ?>
	<li><a href="<?php echo $reservable_content->reservation_url; ?>"><?php echo $reservable_content->title; ?></a></li>
<?php endforeach; ?>
</ul>
<h2>Current Reservations</h2>
<div id="content_reservation-fullCalendar"></div>
</div>
<?php else: ?>
<h2>Content List Empty</h2>
<?php endif; ?>
