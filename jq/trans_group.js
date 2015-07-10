var jq = jQuery.noConflict();
var url=window.location.search.toString();
var room ;
var transmittername ;
var transmitterimage ;
function back(){
	window.location.assign("groupsetting_self.html?"+url);
}

function selectroom(){
	start();
	document.getElementById("turnRoom").click();
}
function getgroupname(){
	return url.split("=")[1];
}
var roomAll;
function start(){
	// //////发送请求到后端，返回整个房间数
	jq.ajax({
		type : "GET",
		url : "/smartHome",
		data : "action=110&readroom=01",
		dataType : "text",
		success : function(data) {
			roomAll = data;
			roomAll = roomAll.split("=")[1];
			roommessage(roomAll);
		}
	});
}
function roommessage(roomALL) {
	var a = 1;
	var number = parseInt(roomALL) + 1;
	jq(".room_mark").remove();
	for (var i = 1; i < number; i++) {
		jq.ajax({
					type : "GET",
					url : "/smartHome",
					data : "action=111&readroom=00&time=" + a,
					dataType : "text",
					success : function(data) {
						var room = data.split("&")[0];
						var roomname = room.split("=")[1];
						var Icon = data.split("&")[1];
						var roomIcon = Icon.split("=")[1];
						html = "<li class='room_mark'><a class='hehe' style='vertical-align: middle; line-height: 60px;'><img src='./images/"
								+ roomIcon
								+ "'style='width:50%'>"
								+ roomname
								+ "</a></li>";
						showRoom(html);
					}
				});
		a++;
	}
	;
};

function showRoom(html) {
	jq("#roomlist").append(html);
	jq("#roomlist").listview("refresh");
	jq(".hehe:last").click(
			function() {
					room = jq(this).html().split(">")[1];
					show(room);
					var roomimage = jq(this).html().split('=')[1].split("/")[2]
					.split('"')[0];
			       jq("#content").parent().html('<img src="./images/'+roomimage+'" style="width:50%" id="content" class="ui-li-thumb">'+room);
			});
}

function show(room){
	jq.ajax({
		url:"/smartHome",
		type:"get",
		data:"action=730&roomname="+room+"&groupname="+getgroupname(),
		dataType:"text",
		success:function(data){
			data=data.substring(data,data.length-1);
			data="["+data+"]";
			var content=eval(data);							
			jq('.ui-dialog').dialog('close');
			showexitTransmitter(content);
		}
	});
}

function showexitTransmitter(content){
	jq(".mark").remove();
	for(var i=0;i<content.length;i++){
	var html = "<li class='mark'><a class='hehe' style='vertical-align: middle; line-height: 60px;'><img src='./images/"
		+ content[i].trasimage+ "'style='width:50%'>"+ content[i].trasname
		+ "</a></li>";
	jq("#exit-divider").after(html);
	jq("#exit").listview("refresh");
	jq(".hehe:first").parents("div[class='ui-btn-inner ui-li']").append(
			"<div class='deletefloat'>remove</div>");
	jq(".hehe:first").on("swipeleft",function() {
				// ///////////此处的含义为伸出删除按钮动画
				jq(".deletefloat").css("width", "0px");
				jq(".ui-btn-text").siblings("span").css("right", "10px");
				jq(this).parents("div .ui-btn-text").siblings(".deletefloat")
						.css("width", "40%");
				jq(this).parents("div .ui-btn-text").siblings("span").css(
						"right", "40%");
			});
	jq(".hehe:first").on("swiperight",function() {
				// ///////////此处的含义为缩进删除按钮动画
				jq(this).parents("div .ui-btn-text").siblings(".deletefloat")
						.css("width", "0px");
				jq(this).parents("div .ui-btn-text").siblings("span").css(
						"right", "10px");
			});
	jq(".deletefloat:first").click(
			function() {
				var transmittername = jq(this).siblings(".ui-btn-text").children("a")
						.html().split(">")[1];
				jq.ajax({
					type : "GET",
					url : "/smartHome",
					data : "action=700&trasname="+transmittername+"&roomname="+room+"&groupname="+getgroupname(),
					dataType : "text",
					success : function(data) {
						if (data.replace(/(^\s*)|(\s*$)/g, "") == "1") {
							show(room);
							alert("remove is successful！！");
						} else {
							alert("remove get error！！！！");
						}
					}
				});
			});
	}
	shownotexitTransmitter();
}

function shownotexitTransmitter(){
	jq.ajax({
		url:"/smartHome",
		type:"get",
		data:"action=731&roomname="+room+"&groupname="+getgroupname(),
		dataType:"text",
		success:function(data){
			data=data.substring(data,data.length-1);
			data="["+data+"]";
			var content=eval(data);	
			for(var i=0;i<content.length;i++){
				var html = "<li class='mark'><a class='he' style='vertical-align: middle; line-height: 60px;'><img src='./images/"
					+ content[i].trasimage+ "'style='width:50%'>"+ content[i].trasname
					+ "</a></li>";
				jq("#no-exit-divider").after(html);
				jq("#exit").listview("refresh");
				jq(".he:first").parents("div[class='ui-btn-inner ui-li']").append(
				"<div class='deletefloat'>add</div>");
		        jq(".he:first").on("swipeleft",function() {
					// ///////////此处的含义为伸出添加按钮动画
					jq(".deletefloat").css("width", "0px");
					jq(".ui-btn-text").siblings("span").css("right", "10px");
					jq(this).parents("div .ui-btn-text").siblings(".deletefloat")
							.css("width", "40%");
					jq(this).parents("div .ui-btn-text").siblings("span").css(
							"right", "40%");
				});
		        jq(".he:first").on("swiperight",function() {
					// ///////////此处的含义为缩进添加按钮动画
					jq(this).parents("div .ui-btn-text").siblings(".deletefloat")
							.css("width", "0px");
					jq(this).parents("div .ui-btn-text").siblings("span").css(
							"right", "10px");
				});
		    	jq(".he:first").parent().siblings(".deletefloat").click(
		    			function() {
		    				transmittername = jq(this).siblings(".ui-btn-text").children("a")
		    						.html().split(">")[1];
		    				transmitterimage = jq(this).siblings(".ui-btn-text").children("a")
    						.children("img").attr("src").split("/")[2];
		    				document.getElementById("turn").click();
		    			});
			}
		}
	});
}

function addTransmitter(){
	jq.ajax({
		type : "GET",
		url : "/smartHome",
		data : "action=701&trasname="+transmittername+"&trasimage="+transmitterimage+"&roomname="+room+"&groupname="+getgroupname(),
		dataType : "text",
		success : function(data) {
			show(room);
		}
	});
}





