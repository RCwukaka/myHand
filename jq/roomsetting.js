var jq = jQuery.noConflict();
var roomIcon;
jq(function() {
	jq(".roomIcon").on("click", function() {
		roomIcon = jq(this).attr("src");
		jq("img").removeClass("tapreflectafter");
		jq(this).addClass("tapreflectafter");
	});
	jq("#sure").click(function() {
		jq("#room_Icon").attr("src", roomIcon);
	});
	///////////�����ʼ��
	jq("#room_Icon").attr("src", "./images/"+getroom().roomimage);
	jq("#Roomname").val(getroom().roomName);
});


////////////����ҳ���еķ������ƺͷ���ͼ��

function getInfo() {
	var roomName = jq("#Roomname").val();
	var roomIcon = jq("#room_Icon").attr("src");
	var roomimage = roomIcon.split("/")[2];
	return {
		"roomName" : roomName,
		"roomimage" : roomimage
	};
}

// ///////����url
function getroom() { // //////�����õ�roomname����
	var room = window.location.toString();
	var roomName = room.split("=")[1].split("&")[0];
	var roomimage=room.split("=")[2];
	return {
		"roomName" : roomName,
		"roomimage" : roomimage
	};
}

// /////url���淿��/////////���ڼ��жϷ����Ƿ����
function urlsaveRoom() {
	var roomName = getInfo().roomName;
	var roomimage = getInfo().roomimage;
	if (roomName != "") {
		if (roomName.length <= 10) {
			if(roomName!="room"){
			jq.ajax({
				type : "GET",
				url : "/smartHome",
				data : "action=101&roomname=" + roomName + "&roomimage="
						+ roomimage,
				dataType : "text",
				success : function(data) {
					var state = data.replace(/(^\s*)|(\s*$)/g, "");
					if (state == "0") {
						alert("������������ԣ���");
					} else if (state == "2") {
						alert("�������ظ����������ķ���������");
					} else if (state == "1") {
						alert("����ɹ�����");
						var myurl = "transmitterlist.html?room=" + getInfo().roomName + "&roomimage="
						+  getInfo().roomimage;
						window.location.assign(myurl);
					}
				}
			});
			}else{
				alert("������������Ϊroom����");
			}
		} else {
			alert("���������ȳ������Ƶ�10�ַ����ȣ�������");
		}
	} else {
		alert("����������Ϊ�գ���");
	}
}

// /////////url�޸ķ������ƣ�������֮ǰ�鿴�Ƿ�������
function urlchangeRoom() {
	var roomName = getInfo().roomName;
	var roomimage = getInfo().roomimage;
	if (roomName != "") {
		if (roomName.length <= 10) {
			if(roomName!="room"){
			jq.ajax({
				type : "GET",
				url : "/smartHome",
				data : "action=120&roomname=" + getroom().roomName + "&newroomname="
						+ roomName + "&newroomimage=" + roomimage,
				dataType : "text",
				success : function(data) {
					var state = data.replace(/(^\s*)|(\s*$)/g, "");
					if (state == "0") {
						alert("�޸ĳ��������ԣ���");
					} else if (state == "2") {
						alert("�������ظ����������ķ���������");
					} else if (state == "1") {
						alert("�޸ĳɹ�����");
						var myurl = "transmitterlist.html?room=" + getInfo().roomName + "&roomimage="
						+  getInfo().roomimage;
				window.location.assign(myurl);
					}
				}
			});
			}else{
				alert("������������Ϊroom����");
			}
		}else {
			alert("���������ȳ������Ƶ�10�ַ����ȣ�������");
		}
	} else {
		alert("����������Ϊ�գ���");
	}
}



///////////�޸ķ������ƣ�������֮ǰ�鿴�Ƿ�������
function changeRoom() {
	var roomName = getInfo().roomName;
	var roomimage = getInfo().roomimage;
	if (roomName != "") {
		if (roomName.length <= 10) {
			if(roomName!="room"){
			jq.ajax({
				type : "GET",
				url : "/smartHome",
				data : "action=120&roomname=" + getroom().roomName + "&newroomname="
						+ roomName + "&newroomimage=" + roomimage,
				dataType : "text",
				success : function(data) {
					var state = data.replace(/(^\s*)|(\s*$)/g, "");
					if (state == "0") {
						alert("�޸ĳ��������ԣ���");
					} else if (state == "2") {
						alert("�������ظ����������ķ���������");
					} else if (state == "1") {
						alert("�޸ĳɹ�����");
					}
				}
			});
			}else{
				alert("������������Ϊroom����");
			}
		}else {
			alert("���������ȳ������Ƶ�10�ַ����ȣ�������");
		}
	} else {
		alert("����������Ϊ�գ���");
	}
}


///////���淿��/////////���ڼ��жϷ����Ƿ����
function saveRoom() {
	var roomName = getInfo().roomName;
	var roomimage = getInfo().roomimage;
	if (roomName != "") {
		if (roomName.length <= 10) {
			if(roomName!="room"){
			jq.ajax({
				type : "GET",
				url : "/smartHome",
				data : "action=101&roomname=" + roomName + "&roomimage="
						+ roomimage,
				dataType : "text",
				success : function(data) {
					var state = data.replace(/(^\s*)|(\s*$)/g, "");
					if (state == "0") {
						alert("������������ԣ���");
					} else if (state == "2") {
						alert("�������ظ����������ķ���������");
					} else if (state == "1") {
						alert("����ɹ�����");
					}
				}
			});
			}else{
				alert("������������Ϊroom����");
			}
		} else {
			alert("���������ȳ������Ƶ�10�ַ����ȣ�������");
		}
	} else {
		alert("����������Ϊ�գ���");
	}
}

var i=true;

// /////////���������Ϣд��url�д��͵�transitter.htmlҳ����
function urlTurn() {
	if(i){
	if (getroom().roomName=="room") {
		urlsaveRoom();
	} else if(getroom().roomName == getInfo().roomName&&getroom().roomimage==getInfo().roomimage){
				var myurl = "transmitterlist.html?room=" + getInfo().roomName + "&roomimage="
						+  getInfo().roomimage;
				window.location.assign(myurl);
	}else{
		urlchangeRoom();
	}
	}else{
		var myurl = "transmitterlist.html?room=" + getInfo().roomName + "&roomimage="
		+  getInfo().roomimage;
window.location.assign(myurl);
	}
}

function changeonsavebut() {
	if (getroom().roomName == getInfo().roomName&&getroom().roomimage==getInfo().roomimage) {
		saveRoom();
	} else if(getroom().roomName=="room"){
		saveRoom();
	}else{
		changeRoom();
	}
	i=false;
}


