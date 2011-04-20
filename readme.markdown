#Drupal Content Reservation Module

## URL Scheme
* /reservations/r/$action_type/$key
	* /reservations/r/type/$content_type
	* /reservations/r/id/$content_id
	* /reservations/r/edit/$reservation_id
* /reservations/j/$query_type/$query_key - Returns an array of fullcalender event objects formatted as json, $query_type is one of either type, nid, uid and $query_key is the appropriate type or id to search for.

## DB Fields
* Reservation Id (rid)
* Associated Node Id (nid)
* Associated User Id (uid)
* Start DateTime (start)
* End DateTime (end)
* Purpose (description)
* Created (created)
* Modified (modified)

## Notes
The calendar display uses a higher version of jquery and is incompatible with 
the jquery packaged with drupal, therefore the module searches for the appropriate
version on first run. Once it finds a version then it stores that internally,
if you update fullcalendar after a first install you must run cron for this
variable to be updated if the packaged version of jquery changes, or manually
execute update_fc_jquery_fname(); somehow.