	//////////ajax���������ʺ�˷���json����
	var jq = jQuery.noConflict();
	var roomAll;
	var state;
	jq(function() {
		////////�������󵽺�ˣ���������������
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
	/////////////���������ѯ
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

	///////����˷��ص�Room��ʾ����,���ҽ�����Ч���ӵ�Ԫ����
	function showRoom(html) {
		jq("#roomlist").append(html);
		jq("#roomlist").listview("refresh");
		
		jq(".hehe:last").click(
				function() {
						var roomname = jq(this).html().split(">")[1];
						var roomimageinit = jq(this).children("img")
								.attr("src");
						roomimage = roomimageinit.split("/")[2]; ///////��ͼƬ·�����зָ��ȡ��ȷͼƬ����
						var myurl = "roomInfo.html?room=" + roomname
								+ "&roomimage=" + roomimage;
						window.location.assign(myurl);
				});
	};
	
	/////////�õ���ǰ������Ŀ��
	function getWindowsWidth(){
		if (window.innerWidth){
			winWidth = window.innerWidth;
		}else if ((document.body) && (document.body.clientWidth)){
			winWidth = document.body.clientWidth;
		}
		return winWidth;	
	}

	////////////���ö���Ч��
	function set(Ele,WindowsWidth){
		jq(Ele).css("left",WindowsWidth);
		setTimeout(function(){
			jq("#setting").addClass("setting");
		}, "1000");
	}

	//////////���ÿ���
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
						alert("�����ɹ���");
					}else{
						alert("�رճɹ���");
						jq("#state").removeClass("ui-btn-active");
					}
				}else{
					if(state==1){
						alert("����ʧ�ܣ�");
						jq("#state").removeClass("ui-btn-active");
					}else{
						alert("�ر�ʧ�ܣ�");
						jq("#state").removeClass("ui-btn-active");
					}
				}
			}
		});
		
	}
