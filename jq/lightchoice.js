	var jq = jQuery.noConflict();

	/////////////后端接受亮度数据
	jq(function() {
		jq.ajax({
			type : "GET",
			url : "/smartHome",
			data : "checkLight",
			dataType : "text",
			success : function(data) { ///data为后端接受的数据，只是一个数据字符串，待修改
				jq("#slider").val(data);
				jq("#slider").slider("refresh");
			}
		});

		var data;
		////////////动态改变亮度，随时发送数据
		jq("#slider").change(function() {
			data = jq("#slider").val();
			alert(data);
			jq.ajax({
				type : "GET",
				url : "/smartHome",
				data : data,
				dataType : "text",
				success : function(data) { ///////////考虑到服务器的反应速度有点慢 此处待改进
					
				}
			});
		});

		////////////////提交理想的亮度数据并保存
		jq("#lightsend").click(function() {
			jq.ajax({
				type : "GET",
				url : "/smartHome",
				data : data, ////////////////将所选的数据提交到后端
				dataType : "text",
				success : function(data) { ///data为后端接受的数据，只是一个数据字符串，待修改
					alert(data); ///////////检验数据
				}
			});
		});
	});