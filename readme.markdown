#Drupal Content Reservation Module

## URL Scheme
* /reservations/r/$content_type - Displays a list and calendar of reservable content for parameter $content_type
* /reservations/r/$content_type/$id - Displays a form to add a reservation for the content with specified $id, as well as a calendar for reservations of that content.
* /reservations/j/$query_type/$query_key - Returns an array of fullcalender event objects formatted as json, $query_type is one of either type, nid, uid and $query_key is the appropriate type or id to search for.

## DB Fields
* Associated Node Id
* Associated User Id
* Start DateTime
* End DateTime
* Purpose

## Notes
The calendar display uses a higher version of jquery and is incompatible with 
the jquery packaged with drupal, therefore the module searches for the appropriate
version on first run. Once it finds a version then it stores that internally,
if you update fullcalendar after a first install you must run cron for this
variable to be updated if the packaged version of jquery changes.