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

///////����˷��ص�group��ʾ����,���ҽ�����Ч���ӵ�Ԫ����
function showgroup(html) {
	jq("#grouplist").append(html);
	jq("#grouplist").listview("refresh");		
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
					var groupname = jq(this).html().split(">")[1];
					var myurl = "groupsetting_self.html?groupname=" + groupname;
					window.location.assign(myurl);
				}
			});
	// /////////ɾ��div��ǩ�����ҽ���Ӧ�ķ���ɾ��
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
							alert("ɾ���ɹ�����");
							check = true;
						} else {
							alert("ɾ������������");
						}
					}
				});
			});

	
};



/////////////group_init()�龰���ʼ��
function group_init(){
		var myurl = "groupsetting_self.html?groupname=group";
		window.location.assign(myurl);
}





















