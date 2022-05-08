<?php

		if (mysqli_errno($conn) != 0) {
		  	$clean_sqlerror = $purifier->purify(mysqli_error($conn));
    		echo $clean_sqlerror; 
  		}