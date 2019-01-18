<?php
    include "Conexion.php";

    if(!$con)
    {
        echo "fallo";
    }
    else{

    $temperatura = $_GET['t'];
    $humedad = $_GET['h'];
    $humedadTierra = $_GET['ht'];

        $query ="INSERT INTO datos (temperatura,humedad,humedad_tierra,fecha) values ($temperatura,$humedad,$humedadTierra,now())";

        mysqli_query($con, $query);
    }   

?>