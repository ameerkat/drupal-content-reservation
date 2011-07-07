<?php if($content_list): ?>
<div id="content_reservation_list-wrapper" class="content_reservation">
<table><tr><td id="content_reservation-fullCalendar-td">
<div id="content_reservation-fullCalendar"></div>
</div>
</td><td style="width: 200px;" id="content_reservation_list_td">
<ul id="content_reservation_list" class="content_reservation">
<?php foreach($content_list as $reservable_content): ?>
	<li><div class="colorBlock" style="background-color: <?php echo $reservable_content->color; ?>;"></div><a href="<?php echo $reservable_content->reservation_url; ?>"><?php echo $reservable_content->title; ?></a></li>
<?php endforeach; ?>
</ul></td></tr></table>
<?php else: ?>
<h2>Content List Empty</h2>
<?php endif; ?>
