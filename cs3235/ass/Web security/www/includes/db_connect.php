<?php
define("HOST", "localhost");     // The host you want to connect to.
define("USER", "cs3235");    // The database username. 
define("PASSWORD", "v29AcujVSDKWadxe");    // The database password. 
define("DATABASE", "cs3235");    // The database name.

$conn = new mysqli(HOST, USER, PASSWORD, DATABASE);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
