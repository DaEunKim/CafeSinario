<!DOCTYPE html>
<html>
    
<title>DaEunTeam UI</title>

<meta http-equiv="Content-Type" content="text/html; charset=euc-kr">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="http://www.w3schools.com/lib/w3.css">
<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Lato">
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">

    <style>
html,body,h1,h2,h3,h4 {font-family:"Lato", sans-serif}
.mySlides {display:none}
.w3-tag, .fa {cursor:pointer}
.w3-tag {height:15px;width:15px;padding:0;margin-top:6px}
</style>
<body>



<!-- Links (sit on top) -->
<div class="w3-top">
<div class="w3-row w3-large">
<div class="w3-col s3">
<a href="#" class="w3-btn-block w3-light-grey">Home</a>
</div>
<div class="w3-col s3">
<a href="#plans" class="w3-btn-block w3-light-grey">Menu</a>
</div>
<div class="w3-col s3">
<a href="#about" class="w3-btn-block w3-light-grey">Order List</a>
</div>
<div class="w3-col s3">
<a href="#contact" class="w3-btn-block w3-light-grey">Order Result</a>
</div>
</div>
</div>


<!-- Content -->
<div class="w3-content" style="max-width:1100px;margin-top:80px;margin-bottom:80px">

<div class="w3-panel">
<h1><b>Cafe Managment Project</b></h1>
<p>DaEun && Hanul && ChangHyeun</p>
</div>

<!-- Slideshow -->
<div class="w3-container">
<img src="coffee2.jpg" style="width:100%">
</div>

<!-- Grid -->
<div class="w3-row-padding" id="plans">
<div class="w3-center w3-padding-64" style="background-color:#ffffe6">
<b style="font-size: 28px; color: #b30000"> 커피 주문 하는 법 </b><br>
<p style="font-size: 16px">주문할 커피이름을 찾는다. <br> 커피이름 오른쪽에 주문하고 싶은 만큼 커피의 수량을 적는다. <br> 메뉴 하단에 Submit 버튼을 눌러서 주문 결과를 바리스타에게 전송한다. <br> 주문 내역서에 내가 주문한 커피가 맞는지 확인한다. <br> 주문한 커피가 완성되면 주문 결과서를 본다.   </p>
<p style="font-size: 16px">** 입력란 바로 아래는 커피마다 걸리는 시간 입니다. <br>
** 메뉴 하단의 Total Time은 주문한 커피에 따른 총 갯수와 총 시간을 표시해줍니다. </p>
</div>

<!-- Total time -->
<script language="javascript">
<!-- Load Menu -->
function init(){
    var nMenu = 13;
    
    var menuName = ['Espresso', 'Americano', 'Cafe Latte', 'Cappuccino', 'Cafe Mocca', 'Frappuccino', 'JavaChip Frappuccino', 'Mint Choco', 'Cocoa', 'Orange Juice', 'Grapefruit Juice', 'Lemon Ade', 'Strawberry Ade'];
    var cost = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13];
    
    var output = '';
    for(var i=0; i<nMenu; ++i){
        output += '<li class="w3-padding-16" >';
        
        output += '<b style="color:#b30000; font-size:35px">' + menuName[i]+ '</b>' ;
        output += '<b style="color:#663300; font-size:15px">       ' + cost[i] + '초 </b>';
        output += '<div class="w3-right" style="font-size:17px;font-family:Helvetica">'+' 커피수 입력 : <input id="coffee'+ i +'" name="coffee' + i + '" type="text" size="2" value="0" onclick="this.select();"/>'+'<br>';
        
        output += '<b id="coffee' + i + 'Total">0초</b>'+'</div>';
        
        output += '</li>';
        
    }
    
    document.getElementById("menuList").innerHTML = output;
}

<!-- Calculate Total Time -->
function updateAll(){
    
    var nMenu = 13;
    
    var coffee = [];
    for(var i=0; i<nMenu; ++i)
        coffee.push(document.getElementById("coffee"+i).value);
	
    var cost = [];
    for(var i=0; i<nMenu; ++i)
        cost.push((i+1)*coffee[i]);
    
    for(var i=0; i<nMenu; ++i)
        document.getElementById("coffee" + i + "Total").innerHTML = "<b size=\"5\"> " + cost[i] + "초</b>";
    
    var totalNumber = 0;
    for(var i=0; i<nMenu; ++i)
        totalNumber += parseInt(coffee[i]);
    document.getElementById("totalNumber").value = totalNumber;
    
    var totalPrice = 0;
    for(var i=0; i<nMenu; ++i)
        totalPrice += parseInt(cost[i]);
    document.getElementById("totalPrice").value = totalPrice;
}

</script>



<?php
    $coffee = [];
    
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        for($i=0; $i<13; $i++){
            $coffee[$i] = $_POST["coffee".$i];
        }
    }
    ?>

<div class="w3-twice w3-margin-bottom">
<ul class="w3-ul w3-border w3-hover-shadow">
<li class="w3-black w3-large w3-center w3-padding-30"><b style="font-size:50px">Menu</b></li>

<form method="post" action="<?php echo $_SERVER["PHP_SELF"];?>" onchange="updateAll()">


<!-- Menu List -->
<div id="menuList"></div>

<script language="javascript">
init();
</script>


<li class="w3-light-grey w3-padding-24">
<!-- <input type="submit" size="10" name="submit" value="Submit"> -->
</li>
<li class="w3-padding-16 w3-center">
<b class="w3-wide" style="color:#cc0066; font-size:35px"> Total Time </b>
<br><b style="color:#1a0d00"> 총 수량 </b> : <input id="totalNumber" type="text" size="4" value="  0"/>
<br><b style="color:#1a0d00"> 총 합계 </b> : <input id="totalPrice" type="text" size="4" value="  0"/>
<br><br><input type="reset" value="초기화" style="color:#1a0d00; font-size:18px"><br>
</li>

<li class="w3-light-grey w3-center w3-padding-24">
	
<input class='w3-padding-middle' type="text" name="orderTime" style='width:15%; font-size:20px; color:#003366; background-color:#e6f2ff' placeholder='주문시간입력란'>

	<form method="post">
<button class='w3-btn w3-padding-large' style='font-size:20px; background-color:#00004d'>Submit </button></form>
<?php 
if ($_SERVER["REQUEST_METHOD"] == "POST"){
    unlink("result.json");} 
?>

</li>
</form>
</ul>
</div>
</div>

<!-- Grid -->
<div id="about"><br><br> </div>
<div class="w3-row-padding w3-center" style="background-color:#ffffe6"><br>
<b class="w3-xlarge w3-bottombar w3-border-dark-grey w3-padding-20" style="color:#cc0066; font-size:40px"> 주문 내역서 </b>
<br><br>
<?php
	$orderTime = $_POST['orderTime'];
    $cost = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13];
    $menuName = ['Espresso', 'Americano', 'Cafe Latte', 'Cappuccino', 'Cafe Mocca', 'Frappuccino', 'JavaChip Frappuccino', 'Mint Choco', 'Cocoa', 'Orange Juice', 'Grapefruit Juice', 'Lemon Ade', 'Strawberry Ade'];
    
    
    $file = fopen("order.json", "a+") or die("Unable to open file!");
    $root = array();
    for($i=0; $i<13; $i++){
        if($coffee[$i]!=0 and is_numeric($coffee[$i])){
            echo "<$i> $menuName[$i] : $coffee[$i]<br>";
            array_push($root, array("Order Time"=>(int)($orderTime) , "id"=>$i, "quantity"=>(int)($coffee[$i])));
        }
    }
    $now = time();
    
    if(filesize("order.json") == 0){
        fwrite($file, "{\n\"$now\":".json_encode($root)."}");
    }
    else{
        $str = fread($file, filesize("order.json")-1);
        fclose($file);
        
        $file = fopen("order.json", "w") or die("Unable to open file!");
        fwrite($file, $str.",\n\"$now\":".json_encode($root)."}");
    }
    fclose($file);
    
    ?>
<br><br><br><br><br><br><br>

</div>
<div>
<br></div>

<div id="contact"><br><br> </div>
<div class="w3-row-padding w3-center" style="background-color:#ffffe6" ><br>
<b class="w3-xlarge w3-bottombar w3-border-dark-grey w3-padding-20" style="color:#cc0066; font-size:40px"> 주문 결과서 </b>
<br><br>


<!--json파일 받아와서 출력하기-->
<?php
	$string = file_get_contents("result.json");
	$data = json_decode($string, true);
    
    $nOrder = 0;
    foreach ($data as $value){
        echo "<b style='font-size:20px'>주문번호 : ",$nOrder++."</b><br>";
        for($i=0; $i<13; $i++)
            echo $menuName[$i]." ".$value[$i]."<br>";
        echo "<b>orderTime : ".$value["orderTime"]."</b><br>";
        echo "<b>endTime : ".$value["endTime"]."</b><br><br>";
    }
?>
<br>

<br><br><br><br><br><br><br><br>
</div>
</div>

<!-- Footer -->
<footer class="w3-container w3-padding-20 w3-light-grey w3-center">
<h4>This cafe's co-CEOs</h4>
<img src="award.jpeg" style="width:50%"><br>
<h5>20113313_이창현 : 20113336_채한울 : 20135179_김다은 </h5>
<a href="#" class="w3-btn w3-padding w3-black w3-margin"><i class="fa fa-arrow-up w3-margin-right"></i>To the top</a>
</footer>
</body>
</html>

