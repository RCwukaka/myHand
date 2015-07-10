var jq = jQuery.noConflict();
jq.ajax({
			type : "GET",
			url : "/smartHome",
			data : "action=610&read_group=0",
			dataType : "text",
			success : function(data) {
				groupAll = data;
				groupAll = groupAll.split("=")[1];
				groupmessage(groupAll);
			}
		});	

function groupmessage(groupAll) {
	var a = 1;
	var number=parseInt(groupAll)+1;
	for (var i = 1; i < number; i++) {			
		jq.ajax({
					type : "GET",
					url : "/smartHome",
					data : "action=611&read_group=1&time=" + a,
					dataType : "text",
					success : function(data) {
						var groupname = data.split("=")[1];
						html = "<li><a class='hehe' style='vertical-align: middle; line-height: 60px;'><img src='./images/ic-ba.png'style='width:50%'>"
								+ groupname + "</a></li>";
						showgroup(html);
					}
				});
		a++;
	};
};

///////将后端返回的group显示出来,并且将滑动效果加到元素上
function showgroup(html) {
	jq("#grouplist").append(html);
	jq("#grouplist").listview("refresh");		
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
					var groupname = jq(this).html().split(">")[1];
					var myurl = "groupsetting_self.html?groupname=" + groupname;
					window.location.assign(myurl);
				}
			});
	// /////////删除div标签，并且将对应的房间删除
	jq(".deletefloat:last").click(
			function(e) {
				var groupname = jq(this).siblings(".ui-btn-text").children("a")
						.html().split(">")[1];
				var group = jq(this).parents("li");
				jq.ajax({
					type : "GET",
					url : "/smartHome",
					data : "action=600&groupname="+groupname,
					dataType : "text",
					success : function(data) {
						if (data.replace(/(^\s*)|(\s*$)/g, "") == "1") {
							group.css("display", "none");
							alert("删除成功！！");
							check = true;
						} else {
							alert("删除出错！！！！");
						}
					}
				});
			});

	
};



/////////////group_init()情景组初始化
function group_init(){
		var myurl = "groupsetting_self.html?groupname=group";
		window.location.assign(myurl);
}





















