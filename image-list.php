<?php

$imagesDir = "images"; // Directory where images are stored.
$imageList = [];       // Creation of empty array to store image file names.

$files = scandir($imagesDir); //scan directory specified and retrieve files.
foreach ($files as $file) {  // loop through each file in directory.
    if (is_file($imagesDir . "/" . $file)) { // Checks if current element ($file) is a file.
        $imageList[] = $file; // if it is a file the file name is added to $imageList array.
    }
}

$lastModified = filemtime($imagesDir); // Retrieving time stamp of last modification made to directory.

header("Content-Type: application/json; charset=utf-8"); // setting content type to JSON format for HTTP response.
echo json_encode(['imageList' => $imageList, 'lastModified' => $lastModified]); // Encodes array's listed as a JSON string.

// PULLING IMAGES AND IMAGE NAMESFROM DIRECTORY