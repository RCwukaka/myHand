var jq = jQuery.noConflict();
var transmitterIcon;// //////遥控器的图标
var trasimageImg;// ///遥控器原先图标
var room;// //////////////这个遥控器对应的房间号
var trasname;// //////////遥控器名称
var stateString = "able";// //////state状态
var roomimage;// ////这个遥控器对应的房间图标
var dataInfo = new Array(5);// ///////遥控器的时间信息
var newtrasname;
var change=false;

// ////////得到遥控器的名称
function gettransmittername() {
	var tras = window.location.toString();
	trasimageImg = tras.split("=")[4];
	var trasname_hehe = tras.split("=")[3];
	trasname = trasname_hehe.split("&")[0];
	var roomparama = tras.split("=")[1];
	room = roomparama.split("&")[0];
	var roomimageparama = tras.split("=")[2];
	roomimage = roomimageparama.split("&")[0];
	jq("#transmitterIcon").attr("src", "./images/" + trasimageImg); // ///////初始化遥控器图片
	jq("#TransmitterName").val(trasname);
}

function back() {
	window.location.assign("transmitterlist.html?room=" + room + "&roomimage="
			+ roomimage);
}

// /////////////时间选择器绑定
jq(function() {
	gettransmittername();

	jq(".transmitterIcon").on("click", function() {
		transmitterIcon = jq(this).attr("src");
		jq("img").removeClass("tapreflectafter");
		jq(this).addClass("tapreflectafter");
	});
	jq("#Iconsure").click(function() {
		jq("#transmitterIcon").attr("src", transmitterIcon);
	});

	// //////////////////////////
	if(trasname!="trans"){
	// ////////返回滚轮通道0的默认值
		backchannel(room,trasname,0,true);
	}
});
function backchannel(room,trasname,channel,state){
	jq.ajax({
		type : "GET",
		url : "/smartHome",
		data : "action=212&readtransmitter=02&roomname=" + room + "&trasname="
				+ trasname+"&channel="+channel,
		dataType : "text",
		success : function(data) {
			data = data.replace(/(^\s*)|(\s*$)/g, "");
			if (data != "") {
				dataInfo = data.split("&");
				for (var i = 0; i < dataInfo.length; i++) {
					dataInfo[i] = dataInfo[i].split("=")[1];
				}
				dataInfo[4]=checkchannel(channel);
				if (parseInt(dataInfo[3]) == 0) {
					stateString = "disable";
				}else{
					stateString="able";
				}
				scroll(dataInfo,state,stateString);					
			} else {
				alert("遥控器不存在!!!");
			}
		}
	});
}

function setchannel(room,trasname,channel,hour,minute,workday,state){
	
	jq.ajax({
		type : "GET",
		url : "/smartHome",
		data : "action=202&roomname="+room+"&trasname="+trasname+"&channel="+channel
		+"&hour="+hour+"&minute="+minute+"&workday="+workday+"&state="+state,
		dataType : "text",
		success : function(data) {			
		}
	});
}

function channelcheck(channel){
	var check=["通道1打开",
	           "通道1关闭",
	           "通道2打开",
	           "通道2关闭",
	           "通道3打开",
	           "通道3关闭",
	           "通道4打开",
	           "通道4关闭",
	           "通道5打开",
			   "通道5关闭",
			   "通道6打开",
			   "通道6关闭",
			   "通道7打开",
			   "通道7关闭",
			   "通道8打开",
			   "通道8关闭"];
	for(var i=0;i<check.length;i++){
		if(check[i]==channel){
			channel=i;
			break;
		};
	}
	return channel;
}

function checkchannel(channel){
	var check=["通道1打开/",
	           "通道1关闭/",
	           "通道2打开/",
	           "通道2关闭/",
	           "通道3打开/",
	           "通道3关闭/",
	           "通道4打开/",
	           "通道4关闭/",
	           "通道5打开/",
			   "通道5关闭/",
			   "通道6打开/",
			   "通道6关闭/",
			   "通道7打开/",
			   "通道7关闭/",
			   "通道8打开/",
			   "通道8关闭/"];
	return check[channel];
}

var mermory="通道1打开";
function scroll(dataInfo,aa,stateString) {
	var optOne = {
		theme : 'sense-ui', // 皮肤样式
		display : 'modal', // 显示方式
		mode : 'scroller', // 日期选择模式
		stepMinute : 1,
		cancelText : "OK",
		lang : 'zh',
		onChange:function(valueText, inst){
			if(valueText.split("/")[0]!=mermory){
				backchannel(room,newtrasname,channelcheck(valueText.split("/")[0]),false);
				mermory=valueText.split("/")[0];
			}		
		},
		onSelect:function(valueText, inst){
			inst.show();
			var hour_param=valueText.split("/")[1];
			var hour=hour_param.split(":")[0]+":";
			var minute_param=valueText.split("/")[1];
			var minute=minute_param.split(":")[1];
			var workday=valueText.split("/")[2];				
			setchannel(room,newtrasname,channelcheck(valueText.split("/")[0]),hour,minute,workday,stateString);
		},
		button3 : state,
		button3Text : stateString,
		rows : 5,
		wheels : [ {
			"通道" : {				
				"通道1打开/" : "1/UP",
				"通道1关闭/" : "1/DN",
				"通道2打开/" : "2/UP",
				"通道2关闭/" : "2/DN",
				"通道3打开/" : "3/UP",
				"通道3关闭/" : "3/DN",
				"通道4打开/" : "4/UP",
				"通道4关闭/" : "4/DN",
				"通道5打开/" : "5/UP",
				"通道5关闭/" : "5/DN",
				"通道6打开/" : "6/UP",
				"通道6关闭/" : "6/DN",
				"通道7打开/" : "7/UP",
				"通道7关闭/" : "7/DN",
				"通道8打开/" : "8/UP",
				"通道8关闭/" : "8/DN"
			},
			"小时" : {
				"--:":"--",
				"0:" : "0点",
				"1:" : "1点",
				"2:" : "2点",
				"3:" : "3点",
				"4:" : "4点",
				"5:" : "5点",
				"6:" : "6点",
				"7:" : "7点",
				"8:" : "8点",
				"9:" : "9点",
				"10:" : "10点",
				"11:" : "11点",
				"12:" : "12点",
				"13:" : "13点",
				"14:" : "14点",
				"15:" : "15点",
				"16:" : "16点",
				"17:" : "17点",
				"18:" : "18点",
				"19:" : "19点",
				"20:" : "20点",
				"21:" : "21点",
				"22:" : "22点",
				"23:" : "23点"
			},
			"分钟" : {
				"--":"--",
				"0" : "00",
				"1" : "01",
				"2" : "02",
				"3" : "03",
				"4" : "04",
				"5" : "05",
				"6" : "06",
				"7" : "07",
				"8" : "08",
				"9" : "09",
				"10" : "10",
				"11" : "11",
				"12" : "12",
				"13" : "13",
				"14" : "14",
				"15" : "15",
				"16" : "16",
				"17" : "17",
				"18" : "18",
				"19" : "19",
				"20" : "20",
				"21" : "21",
				"22" : "22",
				"23" : "23",
				"24" : "24",
				"25" : "25",
				"26" : "26",
				"27" : "27",
				"28" : "28",
				"29" : "29",
				"30" : "30",
				"31" : "31",
				"32" : "32",
				"33" : "33",
				"34" : "34",
				"35" : "35",
				"36" : "36",
				"37" : "37",
				"38" : "38",
				"39" : "39",
				"40" : "40",
				"41" : "41",
				"42" : "42",
				"43" : "43",
				"44" : "44",
				"45" : "45",
				"46" : "46",
				"47" : "47",
				"48" : "48",
				"49" : "49",
				"50" : "15",
				"51" : "51",
				"52" : "52",
				"53" : "53",
				"54" : "54",
				"55" : "55",
				"56" : "56",
				"57" : "57",
				"58" : "58",
				"59" : "59"
			},
			"工作天" : {
				"/--":"--",
				"/Mon" : "Mon",
				"/Tue" : "Tue",
				"/Wed" : "Wed",
				"/Thr" : "Thr",
				"/Fir" : "Fir",
				"/Sat" : "Sat",
				"/Sun" : "Sun",
				"/Mon,Wed,Fir" : "Mon,Wed,Fir",
				"/Tue,Thr,Sat" : "Tue,Thr,Sat",
				"/Workday" : "Workday",
				"/Holiday" : "Holiday"
			},
		} ]
	};
	if(aa==true){
		jq('#scroller').mobiscroll('init', optOne);
		jq('#scroller').mobiscroll('setValue',
				[ dataInfo[4], dataInfo[0], dataInfo[1], dataInfo[2]], true, 1);
	}else{
		jq('#scroller').mobiscroll("destroy");
		jq('#scroller').mobiscroll('init', optOne);
		jq('#scroller').mobiscroll('setValue',
				[ dataInfo[4], dataInfo[0], dataInfo[1], dataInfo[2]], true, 1);
		jq('#scroller').mobiscroll("show");
	}
}

function state(){
		if (jq(this).html() == "able") {
			jq(this).html("disable");
			stateString = "disable";
		} else {
			jq(this).html("able");
			stateString = "able";
		}
}
// ////////////保存遥控器
function saveTransmitter(trasname, transmitterIcon) {
	if (trasname != "") {
		if (trasname.length <= 10) {
			if (trasname != "trans") {
				content = "action=201&roomname=" + room + "&trasname="
						+ trasname + "&trasimage=" + transmitterIcon;
				jq.ajax({
					type : "GET",
					url : "/smartHome",
					data : content,
					dataType : "text",
					success : function(data) {
						var state = data.replace(/(^\s*)|(\s*$)/g, "");
						if (state == "1") {
							alert("保存成功！！");
							backchannel(room,trasname,0);
						} else if (state == "0") {
							alert("保存出错！！！！");
						}
					}
				});
			} else {
				alert("遥控器名不能设为trans！！！！");
			}
		} else {
			alert("遥控器名长度超过限制的10字符长度！！！！");
		}
	} else {
		alert("遥控器名不能为空！！");
	}
}

// //////////////修改遥控器信息，每次发送newtrasname->新房间名 trasname->旧房间名...后端直接全部覆盖
function changetransmitterinfo(trasname, newtrasname, transmitterIcon) {
	if (newtrasname != "") {
		if (newtrasname.length <= 10) {
			if (newtrasname != "trans") {
				content = "action=220&roomname=" + room + "&trasname=" + trasname 
				+ "&newtrasname="+ newtrasname + "&newtrasimage="+ transmitterIcon ;
				jq.ajax({
					type : "GET",
					url : "/smartHome",
					data : content,
					dataType : "text",
					success : function(data) {
						var state = data.replace(/(^\s*)|(\s*$)/g, "");
						if (state == "1") {
							alert("修改成功！！");
							backchannel(room,newtrasname,0);
						} else if (state == "0") {
							alert("修改出错！！！！");
						} else if (state == "2") {
							alert("出现重名！！！请修改遥控器名称！");
						}
					}
				});
			} else {
				alert("遥控器名不能设为trans！！！！");
			}
		} else {
			alert("遥控器名长度超过限制的10字符长度！！！！");
		}
	} else {
		alert("遥控器名不能为空！！");
	}
}

// ////////根据遥控器信息的不同进行修改或者保存操作
function changeable() {
	transmitterIcon = jq("#transmitterIcon").attr("src").split("/")[2];
	newtrasname = document.getElementById("TransmitterName").value;
	if (trasname == "trans") {
		saveTransmitter(newtrasname, transmitterIcon);
	} else {
		if (newtrasname == trasname && transmitterIcon == trasimageImg) {
			if (change) {
				changetransmitterinfo(trasname, newtrasname, transmitterIcon);
			} else {
				saveTransmitter(newtrasname, transmitterIcon);
			}
		} else {
			changetransmitterinfo(trasname, newtrasname, transmitterIcon);
		}
	}
}
