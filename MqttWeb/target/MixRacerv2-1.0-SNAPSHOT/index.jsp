<%-- 
    Document   : index
    Created on : 20-06-2019, 14:47:05
    Author     : sidad
--%>


<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html>
    <head>
        <title>MixRacer</title>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
    </head>
    <body>
        <h1>MixRacer</h1>
        <form action="MixController" method="post">
            
          
       <select name="command"> 
            <option value="o" name="o">Kør</option>
            <option value="b" name="b">Bak</option>
            <option value="f" name="f">Stop</option>
            <option value="l" name="l">Venstre</option>
            <option value="r" name="r">Højre</option>
            <option value="s" name="s">Ligeud</option>

</select> <br> <br>
<button type="submit" name="order">GO!</button>
        </form>
        


    </body>
</html>

