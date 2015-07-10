var jq = jQuery.noConflict();
jq(function() {
	///////////情景组初始化
	jq("#Groupname").val(getgroup().Groupname);
});


////////////解析页面中的情景组名称

function getInfo() {
	var Groupname = jq("#Groupname").val();
	return {
		"Groupname" : Groupname,
	};
}

// ///////解析url
function getgroup() { // //////解析得到roomname函数
	var group = window.location.toString();
	var Groupname = group.split("=")[1];
	return {
		"Groupname" : Groupname,
	};
}

// /////url保存情景组/////////二期加判断情景是否存在
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
						alert("保存出错！请重试！！");
					} else if (state == "2") {
						alert("情景名重复！请更换你的情景名！！");
					} else if (state == "1") {
						alert("保存成功！！");
						var myurl = "trans_group.html?groupname=" + Groupname;
						window.location.assign(myurl);
					}
				}
			});
			}else{
				alert("情景名不能设为group啊！");
			}
		} else {
			alert("情景名长度超过限制的10字符长度！！！！");
		}
	} else {
		alert("情景名不能为空！！");
	}
}

// /////////url修改情景组名称，在请求之前查看是否与重名
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
						alert("修改出错！请重试！！");
					} else if (state == "2") {
						alert("情景名重复！请更换你的房间名！！");
					} else if (state == "1") {
						alert("修改成功！！");
						var myurl = "trans_group.html?groupname=" + Groupname;
				window.location.assign(myurl);
					}
				}
			});
			}else{
				alert("情景名不能设为room啊！");
			}
		}else {
			alert("情景名长度超过限制的10字符长度！！！！");
		}
	} else {
		alert("情景名不能为空！！");
	}
}



///////////修改情景组名称，在请求之前查看是否与重名
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
						alert("修改出错！请重试！！");
					} else if (state == "2") {
						alert("情景名重复！请更换你的情景名！！");
					} else if (state == "1") {
						alert("修改成功！！");
					}
				}
			});
			}else{
				alert("情景名不能设为group啊！");
			}
		}else {
			alert("情景名长度超过限制的10字符长度！！！！");
		}
	} else {
		alert("情景名不能为空！！");
	}
}


///////保存情景组/////////二期加判断情景组是否存在
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
						alert("保存出错！请重试！！");
					} else if (state == "2") {
						alert("情景名重复！请更换你的情景名！！");
					} else if (state == "1") {
						alert("保存成功！！");
					}
				}
			});
			}else{
				alert("情景名不能设为room啊！");
			}
		} else {
			alert("情景名长度超过限制的10字符长度！！！！");
		}
	} else {
		alert("情景名不能为空！！");
	}
}

var i=true;

// /////////将情景组的信息写入url中传送到trans_group.html页面中
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


