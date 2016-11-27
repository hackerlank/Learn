package com.alipay.config;

/* *
 *类名：AlipayConfig
 *功能：基础配置类
 *详细：设置帐户有关信息及返回路径
 *版本：3.3
 *日期：2012-08-10
 *说明：
 *以下代码只是为了方便商户测试而提供的样例代码，商户可以根据自己网站的需要，按照技术文档编写,并非一定要使用该代码。
 *该代码仅供学习和研究支付宝接口使用，只是提供一个参考。
	
 *提示：如何获取安全校验码和合作身份者ID
 *1.用您的签约支付宝账号登录支付宝网站(www.alipay.com)
 *2.点击“商家服务”(https://b.alipay.com/order/myOrder.htm)
 *3.点击“查询合作者身份(PID)”、“查询安全校验码(Key)”

 *安全校验码查看时，输入支付密码后，页面呈灰色的现象，怎么办？
 *解决方法：
 *1、检查浏览器配置，不让浏览器做弹框屏蔽设置
 *2、更换浏览器或电脑，重新登录查询。
 */

public class AlipayConfig {
	
	//↓↓↓↓↓↓↓↓↓↓请在这里配置您的基本信息↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	// 合作身份者ID，以2088开头由16位纯数字组成的字符串
	public static String partner = "2088121665672996";
	// 商户的私钥
	//public static String private_key = "wse2vp3y5kbjgxgenlo8wbsg35tspvxo";
	
    public static String private_key = "MIICdwIBADANBgkqhkiG9w0BAQEFAASCAmEwggJdAgEAAoGBALaNi8NZHMBLO2t8WUjqKr/Vmj2TUSJtkcbpmxq9lZc+yv2Jh5zk3BtxM8bfiKgenw5yEu0nn3JAB6aVrizmWq6u8UxgdO9TcFzzZX0nxF/NmkP4DvirQBLgb988NfSg2qkK0Cq3Sic3S1vB3MWcRGA+HqSr8uEUF5g1DyuyWY1rAgMBAAECgYABdahEa5X7Q566AUiFeLnWxtJw45imedHMkVmYISPtDad513uqGXpZDdKoKGljTrte1jKoisSPmUt2XYQC/+SBtZXMhkO5DJkNCe/UVOdeRcEkjDCBOSEWeF/TF1mrtN4fL/1yGGvqmhTiP0w32L+Q5EeHKsWLQtsiJfBkyKArAQJBAOWLXNGtH3D2JVVorsCzaWpNUplve3PA4FFuPFCzPMo7njNqiOG/67mJt+A+AcQzN7AJOcNQjipgiNNjQldYjKECQQDLl7ba35kCrDoQ3G5J5l9duUDXROfmPueVs7rGAjOqvFQRtrCONLmJu53uGFfkFEP9RJa7VxI6nx59vh+TNfKLAkA01eA2jx/Wk4HCaAcZafKQul2R3bxPx4yakcImXStX7WMbuKDrPY7XtSBy6DLl41glF+qIz4j5riCwb398tXAhAkEArdwrfRIBOrUVCR0U2ervebwf0TW4y3jgj4jicQGkWaNmL5JRh78iyqn7nj4PoGhl/zy5c9ZRbNpBUaQwlqg1LQJBAMAOYWel172pPWA9n7Fg1Kn8U00DUY/vnrEM5NW3N9Mwa1JZAggYC3pqKptoK25la973GQ87E8FlBkkuazSvI44=";
    //public static String private_key = "MIICXQIBAAKBgQC2jYvDWRzASztrfFlI6iq/1Zo9k1EibZHG6ZsavZWXPsr9iYec5NwbcTPG34ioHp8OchLtJ59yQAemla4s5lqurvFMYHTvU3Bc82V9J8RfzZpD+A74q0AS4G/fPDX0oNqpCtAqt0onN0tbwdzFnERgPh6kq/LhFBeYNQ8rslmNawIDAQABAoGAAXWoRGuV+0OeugFIhXi51sbScOOYpnnRzJFZmCEj7Q2nedd7qhl6WQ3SqChpY067XtYyqIrEj5lLdl2EAv/kgbWVzIZDuQyZDQnv1FTnXkXBJIwwgTkhFnhf0xdZq7TeHy/9chhr6poU4j9MN9i/kORHhyrFi0LbIiXwZMigKwECQQDli1zRrR9w9iVVaK7As2lqTVKZb3tzwOBRbjxQszzKO54zaojhv+u5ibfgPgHEMzewCTnDUI4qYIjTY0JXWIyhAkEAy5e22t+ZAqw6ENxuSeZfXblA10Tn5j7nlbO6xgIzqrxUEbawjjS5ibud7hhX5BRD/USWu1cSOp8efb4fkzXyiwJANNXgNo8f1pOBwmgHGWnykLpdkd28T8eMmpHCJl0rV+1jG7ig6z2O17Ugcugy5eNYJRfqiM+I+a4gsG9/fLVwIQJBAK3cK30SATq1FQkdFNnq73m8H9E1uMt44I+I4nEBpFmjZi+SUYe/Isqp+54+D6BoZf88uXPWUWzaQVGkMJaoNS0CQQDADmFnpde9qT1gPZ+xYNSp/FNNA1GP756xDOTVtzfTMGtSWQIIGAt6aiqbaCtuZWve9xkPOxPBZQZJLms0ryOO";
	// 支付宝的公钥，无需修改该值
	//public static String ali_public_key  = "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCnxj/9qwVfgoUh/y2W89L6BkRAFljhNhgPdyPuBV64bfQNN1PjbCzkIM6qRdKBoLPXmKKMiFYnkd6rAoprih3/PrQEB/VsW8OoM8fxn67UDYuyBTqA23MML9q1+ilIZwBC2AQ2UBVOrFXfFl75p6/B5KsiNG9zpgmLCUYuLkxpLQIDAQAB";

    public static String ali_public_key = "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCnxj/9qwVfgoUh/y2W89L6BkRAFljhNhgPdyPuBV64bfQNN1PjbCzkIM6qRdKBoLPXmKKMiFYnkd6rAoprih3/PrQEB/VsW8OoM8fxn67UDYuyBTqA23MML9q1+ilIZwBC2AQ2UBVOrFXfFl75p6/B5KsiNG9zpgmLCUYuLkxpLQIDAQAB";
	//↑↑↑↑↑↑↑↑↑↑请在这里配置您的基本信息↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
	

	// 调试用，创建TXT日志文件夹路径
    //public static String log_path = "/home/flyer/CleanProject/serverdir/cleanProject/PayServer/"
	public static String log_path = "D:\\";

	// 字符编码格式 目前支持 gbk 或 utf-8
	public static String input_charset = "utf-8";
	
	// 签名方式 不需修改
	public static String sign_type = "RSA";

}
