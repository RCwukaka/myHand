	var jq = jQuery.noConflict();

	/////////////��˽�����������
	jq(function() {
		jq.ajax({
			type : "GET",
			url : "/smartHome",
			data : "checkLight",
			dataType : "text",
			success : function(data) { ///dataΪ��˽��ܵ����ݣ�ֻ��һ�������ַ��������޸�
				jq("#slider").val(data);
				jq("#slider").slider("refresh");
			}
		});

		var data;
		////////////��̬�ı����ȣ���ʱ��������
		jq("#slider").change(function() {
			data = jq("#slider").val();
			alert(data);
			jq.ajax({
				type : "GET",
				url : "/smartHome",
				data : data,
				dataType : "text",
				success : function(data) { ///////////���ǵ��������ķ�Ӧ�ٶ��е��� �˴����Ľ�
					
				}
			});
		});

		////////////////�ύ������������ݲ�����
		jq("#lightsend").click(function() {
			jq.ajax({
				type : "GET",
				url : "/smartHome",
				data : data, ////////////////����ѡ�������ύ�����
				dataType : "text",
				success : function(data) { ///dataΪ��˽��ܵ����ݣ�ֻ��һ�������ַ��������޸�
					alert(data); ///////////��������
				}
			});
		});
	});