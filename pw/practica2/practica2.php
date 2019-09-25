<?php
	$username="i12bapec";
	$password="i12bapec";
	$ipHOST="oraclepr.uco.es";
	$dbName="i12bapec";

		$conn = new mysqli ($username, $password, $ipHOST, $dbName);
		if ($conn->connect_error)
		die ($conn->connect_error);
		$sql = "SELECT titulo, autor, signatura FROM Libro";

		$sql = "SELECT nombre, apellidos, departamento, sueldo FROM empleados";

?>
		<table border=1>
		<tr>
		<th>Nombre</th>
		<th>Apellidos</th>
		<th>Departamento</th>
		<th>Sueldo</th>
		</tr>
<?php
		$rows = $conn->query ($sql);
		if (!$rows)
		die ($conn->error);
			foreach ($rows as $row)
			{
				echo '<tr><td>'.$row["nombre"].'</td><td>'.$row["apellidos"].'</td><td>'.$row["departamento"].'</td><td>'.$row["sueldo"].'</td></tr>';
			}
		echo "</table>";
		$conn = null;

?>
