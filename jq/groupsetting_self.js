var jq = jQuery.noConflict();
jq(function() {
	///////////�龰���ʼ��
	jq("#Groupname").val(getgroup().Groupname);
});


////////////����ҳ���е��龰������

function getInfo() {
	var Groupname = jq("#Groupname").val();
	return {
		"Groupname" : Groupname,
	};
}

// ///////����url
function getgroup() { // //////�����õ�roomname����
	var group = window.location.toString();
	var Groupname = group.split("=")[1];
	return {
		"Groupname" : Groupname,
	};
}

// /////url�����龰��/////////���ڼ��ж��龰�Ƿ����
function urlsavegroup() {
	var Groupname = getInfo().Groupname;
	if (Groupname != "") {
		if (Groupname.length <= 10) {
			if(Groupname!="group"){
			jq.ajax({
				type : "GET",
				url : "/smartHome",
				data : "action=601&groupname=" + Groupname ,
				dataType : "text",
				success : function(data) {
					var state = data.replace(/(^\s*)|(\s*$)/g, "");
					if (state == "0") {
						alert("������������ԣ���");
					} else if (state == "2") {
						alert("�龰���ظ������������龰������");
					} else if (state == "1") {
						alert("����ɹ�����");
						var myurl = "trans_group.html?groupname=" + Groupname;
						window.location.assign(myurl);
					}
				}
			});
			}else{
				alert("�龰��������Ϊgroup����");
			}
		} else {
			alert("�龰�����ȳ������Ƶ�10�ַ����ȣ�������");
		}
	} else {
		alert("�龰������Ϊ�գ���");
	}
}

// /////////url�޸��龰�����ƣ�������֮ǰ�鿴�Ƿ�������
function urlchangegroup() {
	var Groupname = getInfo().Groupname;
	if (Groupname != "") {
		if (Groupname.length <= 10) {
			if(Groupname!="group"){
			jq.ajax({
				type : "GET",
				url : "/smartHome",
				data : "action=620&groupname="+getgroup().Groupname+"&newgroupname="+Groupname,
				dataType : "text",
				success : function(data) {
					var state = data.replace(/(^\s*)|(\s*$)/g, "");
					if (state == "0") {
						alert("�޸ĳ��������ԣ���");
					} else if (state == "2") {
						alert("�龰���ظ����������ķ���������");
					} else if (state == "1") {
						alert("�޸ĳɹ�����");
						var myurl = "trans_group.html?groupname=" + Groupname;
				window.location.assign(myurl);
					}
				}
			});
			}else{
				alert("�龰��������Ϊroom����");
			}
		}else {
			alert("�龰�����ȳ������Ƶ�10�ַ����ȣ�������");
		}
	} else {
		alert("�龰������Ϊ�գ���");
	}
}



///////////�޸��龰�����ƣ�������֮ǰ�鿴�Ƿ�������
function changeGroup() {
	var Groupname = getInfo().Groupname;
	if (Groupname != "") {
		if (Groupname.length <= 10) {
			if(Groupname!="group"){
			jq.ajax({
				type : "GET",
				url : "/smartHome",
				data : "action=620&groupname="+getgroup().Groupname+"&newgroupname="+Groupname,
				dataType : "text",
				success : function(data) {
					var state = data.replace(/(^\s*)|(\s*$)/g, "");
					if (state == "0") {
						alert("�޸ĳ��������ԣ���");
					} else if (state == "2") {
						alert("�龰���ظ������������龰������");
					} else if (state == "1") {
						alert("�޸ĳɹ�����");
					}
				}
			});
			}else{
				alert("�龰��������Ϊgroup����");
			}
		}else {
			alert("�龰�����ȳ������Ƶ�10�ַ����ȣ�������");
		}
	} else {
		alert("�龰������Ϊ�գ���");
	}
}


///////�����龰��/////////���ڼ��ж��龰���Ƿ����
function saveGroup() {
	var Groupname = getInfo().Groupname;
	if (Groupname != "") {
		if (Groupname.length <= 10) {
			if(Groupname!="group"){
			jq.ajax({
				type : "GET",
				url : "/smartHome",
				data : "action=601&groupname=" + Groupname ,
				dataType : "text",
				success : function(data) {
					var state = data.replace(/(^\s*)|(\s*$)/g, "");
					if (state == "0") {
						alert("������������ԣ���");
					} else if (state == "2") {
						alert("�龰���ظ������������龰������");
					} else if (state == "1") {
						alert("����ɹ�����");
					}
				}
			});
			}else{
				alert("�龰��������Ϊroom����");
			}
		} else {
			alert("�龰�����ȳ������Ƶ�10�ַ����ȣ�������");
		}
	} else {
		alert("�龰������Ϊ�գ���");
	}
}

var i=true;

// /////////���龰�����Ϣд��url�д��͵�trans_group.htmlҳ����
function urlTurnto() {
	if(i){
	if (getgroup().Groupname=="group") {
		urlsavegroup();
		} else if(getgroup().Groupname == getInfo().Groupname){
				var myurl = "trans_group.html?groupname=" + getInfo().Groupname;
					window.location.assign(myurl);
	       		}else{
	       			urlchangegroup();
	       		}
	}else{
		var myurl = "trans_group.html?groupname=" + getInfo().Groupname;
         window.location.assign(myurl);
	}
}

function changeonsavebut() {
	if (getgroup().Groupname == getInfo().Groupname) {
			saveGroup();
		} else if(getgroup().Groupname=="group"){
				saveGroup();
			}else{
				changeGroup();
		}
			i=false;
}


