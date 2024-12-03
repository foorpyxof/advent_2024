<?php

function mul($one, $two) {
  return ($one * $two);
}

$found = 0;

if ($argc < 2) die("No input file!\n");

$infile = file_get_contents($argv[1]);

$mul_calls = [];

preg_match_all("/(mul\([0-9]+,[0-9]+\))/", $infile, $mul_calls);

// var_dump($mul_calls);

$final_result = 0;

foreach ($mul_calls[0] as $call) {
  eval('$final_result += ' . $call . ';');
}

echo $final_result;

?>
