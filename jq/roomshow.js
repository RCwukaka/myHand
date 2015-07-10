//////////ajax带参数访问后端返回json数据
var jq = jQuery.noConflict();
var roomAll;
jq(function() {
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
});

// //////////初始化房间
function room_init() {
	var myurl = "ambiente.html?room=room&roomimage=ic-no.png";
	window.location.assign(myurl);
}

// ///////////单个房间查询
function roommessage(roomALL) {
	var a = 1;
	var number = parseInt(roomALL) + 1;
	for (var i = 1; i < number; i++) {
		jq
				.ajax({
					type : "GET",
					url : "/smartHome",
					data : "action=111&readroom=00&time=" + a,
					dataType : "text",
					success : function(data) {
						var room = data.split("&")[0];
						var roomname = room.split("=")[1];
						var Icon = data.split("&")[1];
						var roomIcon = Icon.split("=")[1];
						html = "<li><a class='hehe' style='vertical-align: middle; line-height: 60px;'><img src='./images/"
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

// /////将后端返回的Room显示出来,并且将滑动效果加到元素上
function showRoom(html) {
	jq("#roomlist").append(html);
	jq("#roomlist").listview("refresh");

	// /////添加动画效果
	var check = true;
	jq("div[class='ui-btn-inner ui-li']:last").append(
			"<div class='deletefloat'>删除</div>");
	jq(".hehe:last").on(
			"swipeleft",
			function() {
				// ///////////此处的含义为伸出删除按钮动画
				check = false;
				jq(".deletefloat").css("width", "0px");
				jq(".ui-btn-text").siblings("span").css("right", "10px");
				jq(this).parents("div .ui-btn-text").siblings(".deletefloat")
						.css("width", "40%");
				jq(this).parents("div .ui-btn-text").siblings("span").css(
						"right", "40%");
			});
	jq(".hehe:last").on(
			"swiperight",
			function() {
				// ///////////此处的含义为缩进删除按钮动画
				jq(this).parents("div .ui-btn-text").siblings(".deletefloat")
						.css("width", "0px");
				jq(this).parents("div .ui-btn-text").siblings("span").css(
						"right", "10px");
				setTimeout(function() {
					check = true;
				}, 1000);
			});
	jq(".hehe:last").click(
			function() {
				if (check) {
					var room = jq(this).html().split(">")[1];
					var roomimage = jq(this).html().split('=')[1].split("/")[2]
							.split('"')[0];
					var myurl = "ambiente.html?room=" + room
							+ "&roomimage=" + roomimage;
					window.location.assign(myurl);
				}
			});
	// /////////删除div标签，并且将对应的房间删除
	jq(".deletefloat:last").click(
			function() {
				var roomname = jq(this).siblings(".ui-btn-text").children("a")
						.html().split(">")[1];
				var room = jq(this).parents("li");
				jq.ajax({
					type : "GET",
					url : "/smartHome",
					data : "action=100&roomname=" + roomname,
					dataType : "text",
					success : function(data) {
						if (data.replace(/(^\s*)|(\s*$)/g, "") == "1") {
							room.css("display", "none");
							alert("删除成功！！");
							check = true;
						} else {
							alert("删除出错！！！！");
						}
					}
				});
			});

};

