<?php

define("TEXT", "ip.txt");
define("DATA", "ip.dat");

unlink(DATA);

$lines = file(TEXT);
$i = 0;
$lastSize = 0;
foreach ($lines as $line) {
    //if ($i >= 10) { die; }
    $line = trim($line);
    if (empty($line)) {
        continue;
    }
    $data = explode("\t", $line);
    if (empty($data)) {
        continue;
    }
    foreach ($data as &$v) {
        $v = trim($v);
    }
    $left = ip2long($data[0]);
    $right = ip2long($data[1]);
    $location = $data[2];
    $d = pack("LLa64", $left, $right, $location);
    error_log($d, 3, DATA);
    $i ++;
    //printf("%u\t%s(%u)\t%s(%u)\t%s\n", $i, $data[0], $left, $data[1], $right, $location);
}

echo $i . " ip ranges\n";


