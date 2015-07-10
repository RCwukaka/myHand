	//////////ajax带参数访问后端返回json数据
	var jq = jQuery.noConflict();
	var groupAll;
	var state;
	var groupname;
	jq(function() {
		////////发送请求到后端，返回整个group数
		jq.ajax({
			type : "GET",
			url : "/smartHome",
			data : "action=610&read_group=01",
			dataType : "text",
			success : function(data) {
				groupAll = data;
				groupAll = groupAll.split("=")[1];
				groupmessage(groupAll);
			}
		});	
	});
	/////////////单个group查询
	function groupmessage(groupAll) {
		var a = 1;
		var number=parseInt(groupAll)+1;
		for (var i = 1; i < number; i++) {			
			jq.ajax({
						type : "GET",
						url : "/smartHome",
						data : "action=611&read_group=00&time=" + a,
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
		jq(".hehe:last").click(function(){
						groupname = jq(this).html().split(">")[1];
						document.getElementById("turn").click();
				});
	};
	
	
	function send(){
		var time=jq("#time").val();
		jq.ajax({
			type : "GET",
			url : "/smartHome",
			data : "action=740&groupname="+groupname+"&time=" + time,
			dataType : "text",
			success : function(data) {
				jq('.ui-dialog').dialog('close');
			}
		});
	}
	
	
	
	
