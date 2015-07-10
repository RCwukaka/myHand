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
		//////秒是一位
		if (10 > second ) {
			if(minute>10||minute==10){
				////////秒是一位 分是两位  时分情况
				if(hour<24&&hour>10||hour==10){
					/////////秒是一位 分时都是两位
				   jq("#time").text(
						"Time:" + hour + ":" + minute + ":0" + second+":"+day);
				}else if (hour<10){
					//////秒 时是一位 分是两位 
					jq("#time").text(
						"Time:0" + hour + ":" + minute + ":0" + second+":"+day);
				}
			}else if(minute<10){
		  ////////秒是一位 分是一位  时分情况
				if(hour<24&&hour>10||hour==10){
					/////////秒是一位 分是一位 时是两位
				   jq("#time").text(
						"Time:" + hour + ":0" + minute + ":0" + second+":"+day);
				}else if (hour<10){
					//////秒是一位 分是一位 时是一位
					jq("#time").text(
						"Time:0" + hour + ":0" + minute + ":0" + second+":"+day);
				}
			}
		} else if (10 < second && second < 60||second==10) {   
		   ///////秒是两位 
			if(minute>10||minute==10){
			///////秒是两位 分是两位 时分情况
				if(hour<24&&hour>10||hour==10){
					/////////秒是两位 分是两位 时是两位
				   jq("#time").text(
						"Time:" + hour + ":" + minute + ":" + second+":"+day);
				}else if (hour<10){
					//////秒是两位 分是两位 时是一位
					jq("#time").text(
						"Time:0" + hour + ":" + minute + ":" + second+":"+day);
				}
				}else if(minute<10){
				///////秒是两位 分是一位 时分情况
					if(hour<24&&hour>10||hour==10){
						/////////秒是两位 分是一位 时是两位
					   jq("#time").text(
							"Time:" + hour + ":0" + minute + ":" + second+":"+day);
					}else if (hour<10){
						//////秒是两位 分是一位 时是一位
						jq("#time").text(
							"Time:0" + hour + ":0" + minute + ":" + second+":"+day);
					}
				}
		}
	}