var flag = 0; 
function Change() {
	s=document.getElementById('text').innerHTML;
	if (flag == 0) {
		//s=s.replace((Атрибут(ами)?,'***');

		var re = new RegExp("Атрибут(ами)?", "gi");
		var myArray = s.replace(re,"***" );
		flag = 1; 
		s = myArray;
	}
	document.getElementById('text').innerHTML=s;
}
