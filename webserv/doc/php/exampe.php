<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Document</title>
</head>
<body>
	<?php
	// juseok >_<
	echo ("<h1>Hello World!</h1>");

	for($i=2;$i<=9;$i++)
	{
		echo $i."단 입니다.<br/>";
		for($j=1;$j<=9;$j++){
			echo $i." X ".$j." = ".($i*$j)."<br/>";
		}
		echo "<br/>";
	}
	?>
</body>
</html>