var jq=jQuery.noConflict();
jq(document).ready(function(){
	jq("#Save").click(function(){
		var password=document.getElementById("password").value;
		var confirmpassword=document.getElementById("ConfirmPassword").value;
		if(password!=confirmpassword){
			alert("�������벻ƥ�� ����������");	
			document.getElementById("password").value="";
			document.getElementById("password").focus();
			document.getElementById("ConfirmPassword").value="";					
			}else if(password.length>3&&password.length<8){
				 jq.ajax({
		             type: "GET",
		             url: "/smartHome",
		             data: "action=301&password="+password,
		             contentType:"text",
		             dataType: "text",
		             success: function(data){
		                    alert("�޸ĳɹ�����");
		               }
		         });
			     }else{
			    	 alert("�����ʽ����ȷ������������!");	
						document.getElementById("password").value="";
						document.getElementById("password").focus();
						document.getElementById("ConfirmPassword").value="";
			     };
	});
	jq("#Remove").click(function(){
		var password=document.getElementById("password").value;
		var confirmpassword=document.getElementById("ConfirmPassword").value;
		if(password!=confirmpassword&&password.length>3&&password.length<8){
			alert("�������벻ƥ�� ����������");	
			document.getElementById("password").value="";
			document.getElementById("password").focus();
			document.getElementById("ConfirmPassword").value="";					
			}else if(password.length>3&&password.length<8){
				 jq.ajax({
		             type: "GET",
		             url: "/smartHome",
		             data:"action=300&state=1",
		             contentType:"text",
		             dataType: "text",
		             success: function(data){
		                    alert("����ɹ�����");
		               }
		         });
			     };
	});
});