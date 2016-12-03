function c_swop(){
	var w, v;
	var j = document.getElementById("select_picture").value;
	var i = document.getElementById("select_frame").value;
	if(i==1)
		{w="w1"}
	if(i==2)
		{w="w2"}
	if(i==3)
		{w="w3"}
	if(i==4)
		{w="w4"}
	if(j==1)
		{v="w1.html"}
	if(j==2)
		{v="w2.html"}
	if(j==3)
		{v="w3.html"}
	if(j==4)
		{v="w4.html"}
	top.frames[w].location.href = v;	
}
