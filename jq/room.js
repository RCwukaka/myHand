	//////////ajax带参数访问后端返回json数据
	var jq = jQuery.noConflict();
	var roomAll;
	var state;
	jq(function() {
		////////发送请求到后端，返回整个房间数
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
		
		jq.ajax({
			type : "GET",
			url : "/smartHome",
			data : "action=401&read_keystate=1",
			dataType : "text",
			success : function(data) {
				data = data.replace(/(^\s*)|(\s*$)/g, "");
				state=parseInt(data);
				if(state==1){
					jq("#state").addClass("ui-btn-active");	
				}else{
					jq("#state").removeClass("ui-btn-active");
				}
			}
		});
		
		 
		set("#setting",getWindowsWidth());
		jq("#showsimple").on("swipeleft",function(){
			set("#setting",0);
		});
		jq("body").on("swiperight",function(){
			set("#setting",getWindowsWidth());
		});
		
	});
	/////////////单个房间查询
	function roommessage(roomALL) {
		var a = 1;
		var number=parseInt(roomALL)+1;
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
							html = "<li><a class='hehe' style='vertical-align: middle; line-height: 60px;'><img src='./images/"
									+ roomIcon
									+ "'style='width:50%'>"
									+ roomname + "</a></li>";
							showRoom(html);
						}
					});
			a++;
		};
	};

	///////将后端返回的Room显示出来,并且将滑动效果加到元素上
	function showRoom(html) {
		jq("#roomlist").append(html);
		jq("#roomlist").listview("refresh");
		
		jq(".hehe:last").click(
				function() {
						var roomname = jq(this).html().split(">")[1];
						var roomimageinit = jq(this).children("img")
								.attr("src");
						roomimage = roomimageinit.split("/")[2]; ///////对图片路径进行分割，提取正确图片名称
						var myurl = "roomInfo.html?room=" + roomname
								+ "&roomimage=" + roomimage;
						window.location.assign(myurl);
				});
	};
	
	/////////得到当前浏览器的宽度
	function getWindowsWidth(){
		if (window.innerWidth){
			winWidth = window.innerWidth;
		}else if ((document.body) && (document.body.clientWidth)){
			winWidth = document.body.clientWidth;
		}
		return winWidth;	
	}

	////////////设置动画效果
	function set(Ele,WindowsWidth){
		jq(Ele).css("left",WindowsWidth);
		setTimeout(function(){
			jq("#setting").addClass("setting");
		}, "1000");
	}

	//////////设置开关
	function setbutton(){
		if(state==1){
			state=0;
		}else{
			state=1;
		}
		jq.ajax({
			type : "GET",
			url : "/smartHome",
			data : "action=400&keystate="+state,
			dataType : "text",
			success : function(data) {
				data = data.replace(/(^\s*)|(\s*$)/g, "");
				if(data==1){
					if(state==1){
						alert("开启成功！");
					}else{
						alert("关闭成功！");
						jq("#state").removeClass("ui-btn-active");
					}
				}else{
					if(state==1){
						alert("开启失败！");
						jq("#state").removeClass("ui-btn-active");
					}else{
						alert("关闭失败！");
						jq("#state").removeClass("ui-btn-active");
					}
				}
			}
		});
		
	}
