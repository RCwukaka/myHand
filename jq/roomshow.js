//////////ajax���������ʺ�˷���json����
var jq = jQuery.noConflict();
var roomAll;
jq(function() {
	// //////�������󵽺�ˣ���������������
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

// //////////��ʼ������
function room_init() {
	var myurl = "ambiente.html?room=room&roomimage=ic-no.png";
	window.location.assign(myurl);
}

// ///////////���������ѯ
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

// /////����˷��ص�Room��ʾ����,���ҽ�����Ч���ӵ�Ԫ����
function showRoom(html) {
	jq("#roomlist").append(html);
	jq("#roomlist").listview("refresh");

	// /////��Ӷ���Ч��
	var check = true;
	jq("div[class='ui-btn-inner ui-li']:last").append(
			"<div class='deletefloat'>ɾ��</div>");
	jq(".hehe:last").on(
			"swipeleft",
			function() {
				// ///////////�˴��ĺ���Ϊ���ɾ����ť����
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
				// ///////////�˴��ĺ���Ϊ����ɾ����ť����
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
	// /////////ɾ��div��ǩ�����ҽ���Ӧ�ķ���ɾ��
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
							alert("ɾ���ɹ�����");
							check = true;
						} else {
							alert("ɾ������������");
						}
					}
				});
			});

};

