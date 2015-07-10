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
	///////////房间初始化
	jq("#room_Icon").attr("src", "./images/"+getroom().roomimage);
	jq("#Roomname").val(getroom().roomName);
});


////////////解析页面中的房间名称和房间图标

function getInfo() {
	var roomName = jq("#Roomname").val();
	var roomIcon = jq("#room_Icon").attr("src");
	var roomimage = roomIcon.split("/")[2];
	return {
		"roomName" : roomName,
		"roomimage" : roomimage
	};
}

// ///////解析url
function getroom() { // //////解析得到roomname函数
	var room = window.location.toString();
	var roomName = room.split("=")[1].split("&")[0];
	var roomimage=room.split("=")[2];
	return {
		"roomName" : roomName,
		"roomimage" : roomimage
	};
}

// /////url保存房间/////////二期加判断房间是否存在
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
						alert("保存出错！请重试！！");
					} else if (state == "2") {
						alert("房间名重复！请更换你的房间名！！");
					} else if (state == "1") {
						alert("保存成功！！");
						var myurl = "transmitterlist.html?room=" + getInfo().roomName + "&roomimage="
						+  getInfo().roomimage;
						window.location.assign(myurl);
					}
				}
			});
			}else{
				alert("房间名不能设为room啊！");
			}
		} else {
			alert("房间名长度超过限制的10字符长度！！！！");
		}
	} else {
		alert("房间名不能为空！！");
	}
}

// /////////url修改房间名称，在请求之前查看是否与重名
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
						alert("修改出错！请重试！！");
					} else if (state == "2") {
						alert("房间名重复！请更换你的房间名！！");
					} else if (state == "1") {
						alert("修改成功！！");
						var myurl = "transmitterlist.html?room=" + getInfo().roomName + "&roomimage="
						+  getInfo().roomimage;
				window.location.assign(myurl);
					}
				}
			});
			}else{
				alert("房间名不能设为room啊！");
			}
		}else {
			alert("房间名长度超过限制的10字符长度！！！！");
		}
	} else {
		alert("房间名不能为空！！");
	}
}



///////////修改房间名称，在请求之前查看是否与重名
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
						alert("修改出错！请重试！！");
					} else if (state == "2") {
						alert("房间名重复！请更换你的房间名！！");
					} else if (state == "1") {
						alert("修改成功！！");
					}
				}
			});
			}else{
				alert("房间名不能设为room啊！");
			}
		}else {
			alert("房间名长度超过限制的10字符长度！！！！");
		}
	} else {
		alert("房间名不能为空！！");
	}
}


///////保存房间/////////二期加判断房间是否存在
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
						alert("保存出错！请重试！！");
					} else if (state == "2") {
						alert("房间名重复！请更换你的房间名！！");
					} else if (state == "1") {
						alert("保存成功！！");
					}
				}
			});
			}else{
				alert("房间名不能设为room啊！");
			}
		} else {
			alert("房间名长度超过限制的10字符长度！！！！");
		}
	} else {
		alert("房间名不能为空！！");
	}
}

var i=true;

// /////////将房间的信息写入url中传送到transitter.html页面中
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


