var jq = jQuery.noConflict();
var dayarray=["Mon","Tues","Wed","Thir","Fir","Sat","Sun"];
var day;
	jq(function() {
		jq.ajax({
			url : "/smartHome",
			type : "get",
			data : "action=500&get_time=1",
			dataType : "text",
			success : function(data) {
				data=data.replace(/(^\s*)|(\s*$)/g, "");
				var hour = parseInt(data.split(":")[0]);
				var minute = parseInt(data.split(":")[1]);
				var second = parseInt(data.split(":")[2]);
				var dayaccount = parseInt(data.split(":")[3]);
				day=dayarray[dayaccount];
				setInterval(function() {
					second++;
					if (second == 60) {
						second=0;
						minute++;
						if(minute==60){
							hour++;
							if(hour<24){
								second=0;
								minute=0;							
								timer(second,minute,hour,day);
							}else if(hour==24){
								second=0;
								minute=0;
								hour=0;
								if(dayaccount==6){
									dayaccount=0;
								}else{
									dayaccount++;
								}
								day=dayarray[dayaccount];
								timer(second,minute,hour,day);
							}							
						}else{
							timer(second,minute,hour,day);
						}
					}
				timer(second,minute,hour,day);
				}, 1000);
			}
		});
	});
	
	function timer(second,minute,hour,day){
		//////����һλ
		if (10 > second ) {
			if(minute>10||minute==10){
				////////����һλ ������λ  ʱ�����
				if(hour<24&&hour>10||hour==10){
					/////////����һλ ��ʱ������λ
				   jq("#time").text(
						"Time:" + hour + ":" + minute + ":0" + second+":"+day);
				}else if (hour<10){
					//////�� ʱ��һλ ������λ 
					jq("#time").text(
						"Time:0" + hour + ":" + minute + ":0" + second+":"+day);
				}
			}else if(minute<10){
		  ////////����һλ ����һλ  ʱ�����
				if(hour<24&&hour>10||hour==10){
					/////////����һλ ����һλ ʱ����λ
				   jq("#time").text(
						"Time:" + hour + ":0" + minute + ":0" + second+":"+day);
				}else if (hour<10){
					//////����һλ ����һλ ʱ��һλ
					jq("#time").text(
						"Time:0" + hour + ":0" + minute + ":0" + second+":"+day);
				}
			}
		} else if (10 < second && second < 60||second==10) {   
		   ///////������λ 
			if(minute>10||minute==10){
			///////������λ ������λ ʱ�����
				if(hour<24&&hour>10||hour==10){
					/////////������λ ������λ ʱ����λ
				   jq("#time").text(
						"Time:" + hour + ":" + minute + ":" + second+":"+day);
				}else if (hour<10){
					//////������λ ������λ ʱ��һλ
					jq("#time").text(
						"Time:0" + hour + ":" + minute + ":" + second+":"+day);
				}
				}else if(minute<10){
				///////������λ ����һλ ʱ�����
					if(hour<24&&hour>10||hour==10){
						/////////������λ ����һλ ʱ����λ
					   jq("#time").text(
							"Time:" + hour + ":0" + minute + ":" + second+":"+day);
					}else if (hour<10){
						//////������λ ����һλ ʱ��һλ
						jq("#time").text(
							"Time:0" + hour + ":0" + minute + ":" + second+":"+day);
					}
				}
		}
	}