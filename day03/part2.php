<?php

$active = TRUE;

function mul($one, $two) {
  return ($one * $two);
}

$found = 0;

if ($argc < 2) die("No input file!\n");

$infile = file_get_contents($argv[1]);

$mul_calls = [];

preg_match_all("/(mul\([0-9]+,[0-9]+\))|(do\(\))|(don't\(\))/", $infile, $mul_calls);

//var_dump($mul_calls);

$final_result = 0;

foreach ($mul_calls[0] as $call) {
  switch(explode('(', $call)[0]) {
    
    case "do":
      $active = TRUE;
      break;

    case "don't":
      $active = FALSE;
      break;

    case "mul":
      if ($active) eval('$final_result += ' . $call . ';');
      break;

  }
}

echo $final_result;

?>
