<?php

function cron_alert_status() {
	
	$to = variable_get('cron_alert_email', 'roger@ossolutions.org');
	$minutes = variable_get('cron_alert_minutes', 20);
	$last_run = variable_get('cron_last', 1);
	$current_time = time();
	$cutoff = $last_run+(1*$minutes*60);
	
	echo 'Cron last ran at ' . gmdate("M d Y H:i:s", $last_run);
	echo '<br>';
	echo 'Cutoff set to ' . gmdate("M d Y H:i:s", $cutoff);
	echo '<br>';
	echo 'Current time is ' . gmdate("M d Y H:i:s", $current_time);
	echo '<br>';
	echo 'Sending email to ' . $to;
	echo '<br>';
	echo 'Minutes set to ' . $minutes;
	echo '<br>';
		
	//Verify that the selected number of minutes has passed time already
	if ($cutoff < $current_time) {
        $error = "Cron run is past due.<br>Check site <a href='/admin/reports/status' target='_blank'>status</a> report.";
        echo $error;
        $from = 'cron@itworld.com';
        $to = variable_get('cron_alert_email', 'roger@ossolutions.org');
		$message = drupal_mail('cron_alert', 'notice', $to, language_default(), $params, $from, TRUE);			
	}

	return;
}
