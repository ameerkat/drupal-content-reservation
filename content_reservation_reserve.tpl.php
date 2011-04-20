<a href="<?php print $variables['variables']['content_link']; ?>" class="content_link">
&lt;&lt; back to <?php print $variables['variables']['content_title'] ?> list</a>
<table><tr><td style="width: 310px; vertical-align: top;">
<?php print $variables['variables']['reservation_form']; ?>
</td><td>
<?php print $variables['variables']['calendar_div']; ?>
</td></tr>
</table>
<?php if(isset($variables['variables']['admin_form'])): ?>
	<?php print $variables['variables']['admin_form']; ?>
<?php endif; ?>