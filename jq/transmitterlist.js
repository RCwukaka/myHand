//////////ajax带参数访问后端返回json数据
	var jq = jQuery.noConflict();
	var transmitterAll;
	var element;
	var roomname;
	var roomimage;
	function getroom() { ////////解析得到roomname和roomimage函数
		var room = window.location.toString();
		roomname = room.split("=")[1].split("&")[0];
		roomimage=room.split("=")[2];
	}
	function back(){
		window.location.assign("ambiente.html?room="+roomname+"&roomimage="+roomimage);
	}
	///////////////初始化遥控器信息
	jq(function() {
		getroom();
		////////发送请求到后端，返回整个遥控器数
		jq("#transmitterinit").click(
			function() {
				var transmitterurl = "transmitter.html?room=" + roomname+"&roomimage="+roomimage+"&trasname=trans&trasimage=tc_6.png";
				window.location.assign(transmitterurl);
			});
		jq.ajax({
			type : "GET",
			url : "/smartHome",
			data : "action=210&readtransmitter=01&roomname=" + roomname, /////////////roomname为定值测试用
			dataType : "text",
			success : function(data) {
				transmitterAll = data;
				transmitterAll = transmitterAll.split("=")[1];
				roommessage(transmitterAll);
			}
		});
	});
	/////////////单个遥控器查询简单信息
	function roommessage(transmitterAll) {
		var a = 1;
		var number=parseInt(transmitterAll)+1;
		for (var i = 1; i < number; i++) {
			jq.ajax({
						type : "GET",
						url : "/smartHome",
						data : "action=211&readtransmitter=00&roomname="
								+ roomname + "&time=" + a,
						dataType : "text",
						success : function(data) {
							var transmitter = data.split("&")[0];
							var transmittername = transmitter.split("=")[1];
							var transmitterparama = data.split("&")[1];
							var transmitterIcon = transmitterparama.split("=")[1];
							html = "<li><a class='hehe' style='vertical-align: middle; line-height: 60px;'><img src='./images/"
									+ transmitterIcon
									+ "'style='width:50%'>"
									+ transmittername + "</a></li>";
							showRoom(html);
						}
					});
			a++;
		};
	};
	///////将后端返回的Room显示出来,并且将滑动效果加到元素上
	function showRoom(html) {
		jq("#transmitterlist").append(html);
		jq("#transmitterlist").listview("refresh");
		var check = true;
		///////////此处为动态添加删除按钮
		jq("div[class='ui-btn-inner ui-li']:last")
				.append(
						"<div class='deletefloat'>删除</div>");
		jq(".hehe:last").on(
				"swipeleft",
				function() {
					check = false;
					/////////////此处的含义为伸出删除按钮动画
					jq(".deletefloat").css("width", "0px");
					jq(".ui-btn-text").siblings("span").css("right", "10px");
					jq(this).parents("div .ui-btn-text").siblings(
							".deletefloat").css("width", "40%");
					jq(this).parents("div .ui-btn-text").siblings("span").css(
							"right", "40%");
				});
		jq(".hehe:last").on(
				"swiperight",
				function() {
					/////////////此处的含义为缩进删除按钮动画			
					jq(this).parents("div .ui-btn-text").siblings(
							".deletefloat").css("width", "0px");
					jq(this).parents("div .ui-btn-text").siblings("span").css(
							"right", "10px");
					setTimeout(function() {
						check = true;
					}, 1000);
				});
		var transmittername; ////////遥控器名字
		var trasimage; ///////遥控器图标

		////////////URL转向
		jq(".hehe:last").click(
				function() {
					if (check) {
						transmittername = jq(this).html().split(">")[1];
						var trasimageinit = jq(this).children("img")
								.attr("src");
						trasimage = trasimageinit.split("/")[2]; ///////对图片路径进行分割，提取正确图片名称
						var myurl = "transmitter.html?room=" + roomname
								+ "&roomimage="+roomimage+"&transmitter=" + transmittername
								+ "&trasimage=" + trasimage;
						window.location.assign(myurl);
					}
				});

		////////////删除遥控器
		jq(".deletefloat:last").click(
				function() {
					transmittername = jq(this)
							.siblings(".ui-btn-text").children("a").html()
							.split(">")[1];
					transmitter = jq(this).parents("li");
					jq.ajax({
						type : "GET",
						url : "/smartHome",
						data : "action=200&trasname=" + transmittername
								+ "&roomname=" + roomname,
						dataType : "text",
						success : function(data) {
							if (data.replace(/(^\s*)|(\s*$)/g, "") == "1") {
								transmitter.css("display", "none");
								alert("删除成功！！！");
								check = true;
							} else {
								alert("删除出错！！！！");
							}
						}
					});
				});
	};