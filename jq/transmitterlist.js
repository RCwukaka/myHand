//////////ajax���������ʺ�˷���json����
	var jq = jQuery.noConflict();
	var transmitterAll;
	var element;
	var roomname;
	var roomimage;
	function getroom() { ////////�����õ�roomname��roomimage����
		var room = window.location.toString();
		roomname = room.split("=")[1].split("&")[0];
		roomimage=room.split("=")[2];
	}
	function back(){
		window.location.assign("ambiente.html?room="+roomname+"&roomimage="+roomimage);
	}
	///////////////��ʼ��ң������Ϣ
	jq(function() {
		getroom();
		////////�������󵽺�ˣ���������ң������
		jq("#transmitterinit").click(
			function() {
				var transmitterurl = "transmitter.html?room=" + roomname+"&roomimage="+roomimage+"&trasname=trans&trasimage=tc_6.png";
				window.location.assign(transmitterurl);
			});
		jq.ajax({
			type : "GET",
			url : "/smartHome",
			data : "action=210&readtransmitter=01&roomname=" + roomname, /////////////roomnameΪ��ֵ������
			dataType : "text",
			success : function(data) {
				transmitterAll = data;
				transmitterAll = transmitterAll.split("=")[1];
				roommessage(transmitterAll);
			}
		});
	});
	/////////////����ң������ѯ����Ϣ
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
	///////����˷��ص�Room��ʾ����,���ҽ�����Ч���ӵ�Ԫ����
	function showRoom(html) {
		jq("#transmitterlist").append(html);
		jq("#transmitterlist").listview("refresh");
		var check = true;
		///////////�˴�Ϊ��̬���ɾ����ť
		jq("div[class='ui-btn-inner ui-li']:last")
				.append(
						"<div class='deletefloat'>ɾ��</div>");
		jq(".hehe:last").on(
				"swipeleft",
				function() {
					check = false;
					/////////////�˴��ĺ���Ϊ���ɾ����ť����
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
					/////////////�˴��ĺ���Ϊ����ɾ����ť����			
					jq(this).parents("div .ui-btn-text").siblings(
							".deletefloat").css("width", "0px");
					jq(this).parents("div .ui-btn-text").siblings("span").css(
							"right", "10px");
					setTimeout(function() {
						check = true;
					}, 1000);
				});
		var transmittername; ////////ң��������
		var trasimage; ///////ң����ͼ��

		////////////URLת��
		jq(".hehe:last").click(
				function() {
					if (check) {
						transmittername = jq(this).html().split(">")[1];
						var trasimageinit = jq(this).children("img")
								.attr("src");
						trasimage = trasimageinit.split("/")[2]; ///////��ͼƬ·�����зָ��ȡ��ȷͼƬ����
						var myurl = "transmitter.html?room=" + roomname
								+ "&roomimage="+roomimage+"&transmitter=" + transmittername
								+ "&trasimage=" + trasimage;
						window.location.assign(myurl);
					}
				});

		////////////ɾ��ң����
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
								alert("ɾ���ɹ�������");
								check = true;
							} else {
								alert("ɾ������������");
							}
						}
					});
				});
	};