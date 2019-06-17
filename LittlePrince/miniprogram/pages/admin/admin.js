//admin.js

//获取应用实例
const app = getApp()

Page({
  /** 页面的初始数据 */
  db: undefined,

  data: {
    canIUse: wx.canIUse('button.open-type.getUserInfo'),
    userInfo: {},
    inPassword: '',
    password: 'abc',  
    schTitle: ['课程', '上课地点', '上课时间'],
    courseList: [],
    notifyList: [],
  },
  
  onLoad: function () {
    var that = this
    // 取得用户信息   
    wx.getSetting({
      success: function (res) {
        if (res.authSetting['scope.userInfo']) {
          wx.getUserInfo({
            success: res => {
              app.globalData.userInfo = res.userInfo
            }
          })
        }
      }
    })

    //  调用login云函数获取openid
    wx.cloud.callFunction({
      name: 'login',
      data: {},
      success: res => {
        console.log('[云函数] [login] user openid: ', res.result.openid)
        app.globalData.openid = res.result.openid
        wx.cloud.init({ env: 'jim72zhou' })
        that.db = wx.cloud.database()
      },
      fail: err => {
        console.error('[云函数] [login] 调用失败', err)
        wx.showModal({
          title: '连接失败',
          content: '请检查网络！',
          showCancel: false
        })
      }
    })
  },

  //  单击“查询课程信息”按钮执行该函数
  queryCourseInfo: function () {
    var that = this;

    //  搜索课程集  
    this.db.collection('course').where({
      student: that.data.student
    }).get({
      success: function (res) {
        console.log('queryCourseInfo count', res.data.length)
        if (res.data.length > 0) {
          that.setData({
            hasCourse: true,
            courseList: res.data,
          })
        }
        else{
          that.setData({
            hasCourse: false,
            cntNotify: -1,
            courseList: [],

          })
        }
      },
      fail: function (res) {
        wx.showModal({
          title: '查询失败',
          content: '没有你要的数据！',
          showCancel: false
        })
      }
    })
  },

  //  单击“显示通知信息”按钮执行该函数
  queryNotifyInfo: function () {
    var that = this;
    var subject1;
    var classType1;
    var courseList = that.data.courseList;
    var notifyListInfo = [];
   
    // 查询通知信息
    that.setData({
      cntNotify: 0,
    })
    for (var idx = 0; idx < courseList.length; idx++) {
      subject1 = courseList[idx].subject;
      classType1 = courseList[idx].classType;

      //  搜索科目，班级对应的通知  
      this.db.collection('notify').where({
        subject: subject1,
        classType: classType1
      }).get({
        success: function (res) {
          if (res.data.length > 0) {
            for (var j = 0; j < res.data.length; j++){
              notifyListInfo.push(res.data[j])
            }
            that.setData({
              cntNotify: notifyListInfo.length,
              notifyList: notifyListInfo,
            })
          }
        },
        fail: function (res) {
          wx.showModal({
            title: '通知查询失败',
            content: '没有通知数据！',
            showCancel: false
          })
        }
      });
    }
  },

  bindKeyInputPassword: function (e) {
    this.setData({
      inPassword: e.detail.value
    })
  },
})

var getNotifyList = function (courseList, notifyCollection) {
  var classType1;
  var subject1;
  var nofifyList = [];

  console.log('getNotifyList-coursr', courseList.length)
  console.log('getNotifyList-notify', notifyCollection.length)
  //  搜索数据集  
  for (var idx = 0; idx < courseList.length; idx++) {
    subject1 = coureList[idx].subject;
    classType1 = coureList[idx].classType;
   
    //  搜索科目，班级对应的通知  
    notifyCollection.where({
      subject: subject1,
      classType: classType1
    }).get({
      success: function (res) {
        if (res.data.length > 0) {
          nofifyList.push(res.data)
        }
      }
    });

    return nofifyList;
  }
}
