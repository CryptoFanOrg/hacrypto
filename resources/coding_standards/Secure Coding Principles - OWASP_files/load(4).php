var mediaWikiLoadStart=(new Date()).getTime();function isCompatible(ua){if(ua===undefined){ua=navigator.userAgent;}return!((ua.indexOf('MSIE')!==-1&&parseFloat(ua.split('MSIE')[1])<6)||(ua.indexOf('Firefox/')!==-1&&parseFloat(ua.split('Firefox/')[1])<3)||ua.match(/BlackBerry[^\/]*\/[1-5]\./)||ua.match(/webOS\/1\.[0-4]/)||ua.match(/PlayStation/i)||ua.match(/SymbianOS|Series60/)||ua.match(/NetFront/)||ua.match(/Opera Mini/)||ua.match(/S40OviBrowser/)||(ua.match(/Glass/)&&ua.match(/Android/)));}var startUp=function(){mw.config=new mw.Map(true);mw.loader.addSource({"local":{"loadScript":"/load.php","apiScript":"/api.php"}});mw.loader.register([["site","1450673896",[],"site"],["noscript","1450673896",[],"noscript"],["startup","1452791638",[],"startup"],["filepage","1450673896"],["user.groups","1450673896",[],"user"],["user","1450673896",[],"user"],["user.cssprefs","1450065524",["mediawiki.user"],"private"],["user.options","1450065524",[],"private"],["user.tokens","1450065524",[],"private"],
["mediawiki.language.data","1450673896",["mediawiki.language.init"]],["mediawiki.skinning.elements","1450673896"],["mediawiki.skinning.content","1450673896"],["mediawiki.skinning.interface","1450673895"],["skins.cologneblue","1450673896"],["skins.modern","1450673896"],["skins.vector.styles","1450673895"],["skins.monobook.styles","1450673896"],["skins.vector.js","1450673896",["jquery.throttle-debounce"]],["skins.vector.collapsibleNav","1452703212",["jquery.client","jquery.cookie","jquery.tabIndex"]],["jquery","1450673896"],["jquery.appear","1450673896"],["jquery.arrowSteps","1450673896"],["jquery.async","1450673896"],["jquery.autoEllipsis","1450673896",["jquery.highlightText"]],["jquery.badge","1450673896",["mediawiki.language"]],["jquery.byteLength","1450673896"],["jquery.byteLimit","1450673896",["jquery.byteLength"]],["jquery.checkboxShiftClick","1450673896"],["jquery.chosen","1450673896"],["jquery.client","1450673896"],["jquery.color","1450673896",["jquery.colorUtil"]],[
"jquery.colorUtil","1450673896"],["jquery.cookie","1450673896"],["jquery.delayedBind","1450673896"],["jquery.expandableField","1450673896"],["jquery.farbtastic","1450673896",["jquery.colorUtil"]],["jquery.footHovzer","1450673896"],["jquery.form","1450673896"],["jquery.fullscreen","1450673896"],["jquery.getAttrs","1450673896"],["jquery.hidpi","1450673896"],["jquery.highlightText","1450673896",["jquery.mwExtension"]],["jquery.hoverIntent","1450673896"],["jquery.json","1450673896"],["jquery.localize","1450673896"],["jquery.makeCollapsible","1452703212"],["jquery.mockjax","1450673896"],["jquery.mw-jump","1450673896"],["jquery.mwExtension","1450673896"],["jquery.placeholder","1450673896"],["jquery.qunit","1450673896"],["jquery.qunit.completenessTest","1450673896",["jquery.qunit"]],["jquery.spinner","1450673896"],["jquery.jStorage","1450673896",["jquery.json"]],["jquery.suggestions","1450673896",["jquery.highlightText"]],["jquery.tabIndex","1450673896"],["jquery.tablesorter","1452703224",[
"jquery.mwExtension","mediawiki.language.months"]],["jquery.textSelection","1450673896",["jquery.client"]],["jquery.throttle-debounce","1450673896"],["jquery.validate","1450673896"],["jquery.xmldom","1450673896"],["jquery.tipsy","1450673896"],["jquery.ui.core","1450673896",[],"jquery.ui"],["jquery.ui.widget","1450673896",[],"jquery.ui"],["jquery.ui.mouse","1450673896",["jquery.ui.widget"],"jquery.ui"],["jquery.ui.position","1450673896",[],"jquery.ui"],["jquery.ui.draggable","1450673896",["jquery.ui.core","jquery.ui.mouse","jquery.ui.widget"],"jquery.ui"],["jquery.ui.droppable","1450673896",["jquery.ui.core","jquery.ui.draggable","jquery.ui.mouse","jquery.ui.widget"],"jquery.ui"],["jquery.ui.resizable","1450673896",["jquery.ui.core","jquery.ui.mouse","jquery.ui.widget"],"jquery.ui"],["jquery.ui.selectable","1450673896",["jquery.ui.core","jquery.ui.mouse","jquery.ui.widget"],"jquery.ui"],["jquery.ui.sortable","1450673896",["jquery.ui.core","jquery.ui.mouse","jquery.ui.widget"],
"jquery.ui"],["jquery.ui.accordion","1450673896",["jquery.ui.core","jquery.ui.widget"],"jquery.ui"],["jquery.ui.autocomplete","1450673896",["jquery.ui.core","jquery.ui.position","jquery.ui.widget"],"jquery.ui"],["jquery.ui.button","1450673896",["jquery.ui.core","jquery.ui.widget"],"jquery.ui"],["jquery.ui.datepicker","1450673896",["jquery.ui.core"],"jquery.ui"],["jquery.ui.dialog","1450673896",["jquery.ui.button","jquery.ui.core","jquery.ui.draggable","jquery.ui.mouse","jquery.ui.position","jquery.ui.resizable","jquery.ui.widget"],"jquery.ui"],["jquery.ui.progressbar","1450673896",["jquery.ui.core","jquery.ui.widget"],"jquery.ui"],["jquery.ui.slider","1450673896",["jquery.ui.core","jquery.ui.mouse","jquery.ui.widget"],"jquery.ui"],["jquery.ui.tabs","1450673896",["jquery.ui.core","jquery.ui.widget"],"jquery.ui"],["jquery.effects.core","1450673896",[],"jquery.ui"],["jquery.effects.blind","1450673896",["jquery.effects.core"],"jquery.ui"],["jquery.effects.bounce","1450673896",[
"jquery.effects.core"],"jquery.ui"],["jquery.effects.clip","1450673896",["jquery.effects.core"],"jquery.ui"],["jquery.effects.drop","1450673896",["jquery.effects.core"],"jquery.ui"],["jquery.effects.explode","1450673896",["jquery.effects.core"],"jquery.ui"],["jquery.effects.fade","1450673896",["jquery.effects.core"],"jquery.ui"],["jquery.effects.fold","1450673896",["jquery.effects.core"],"jquery.ui"],["jquery.effects.highlight","1450673896",["jquery.effects.core"],"jquery.ui"],["jquery.effects.pulsate","1450673896",["jquery.effects.core"],"jquery.ui"],["jquery.effects.scale","1450673896",["jquery.effects.core"],"jquery.ui"],["jquery.effects.shake","1450673896",["jquery.effects.core"],"jquery.ui"],["jquery.effects.slide","1450673896",["jquery.effects.core"],"jquery.ui"],["jquery.effects.transfer","1450673896",["jquery.effects.core"],"jquery.ui"],["moment","1450673896"],["mediawiki","1450673896"],["mediawiki.api","1450673896",["mediawiki.util"]],["mediawiki.api.category","1450673896",[
"mediawiki.Title","mediawiki.api"]],["mediawiki.api.edit","1450673896",["mediawiki.Title","mediawiki.api","user.tokens"]],["mediawiki.api.login","1450673896",["mediawiki.api"]],["mediawiki.api.parse","1450673896",["mediawiki.api"]],["mediawiki.api.watch","1450673896",["mediawiki.api","user.tokens"]],["mediawiki.debug","1450673896",["jquery.footHovzer","jquery.tipsy"]],["mediawiki.debug.init","1450673896",["mediawiki.debug"]],["mediawiki.feedback","1450673896",["jquery.ui.dialog","mediawiki.Title","mediawiki.api.edit","mediawiki.jqueryMsg"]],["mediawiki.hidpi","1450673896",["jquery.hidpi"]],["mediawiki.hlist","1450673896",["jquery.client"]],["mediawiki.htmlform","1452711446"],["mediawiki.icon","1450673896"],["mediawiki.inspect","1450673896",["jquery.byteLength","jquery.json"]],["mediawiki.notification","1450673896",["mediawiki.page.startup"]],["mediawiki.notify","1450673896"],["mediawiki.searchSuggest","1452703212",["jquery.client","jquery.placeholder","jquery.suggestions",
"mediawiki.api"]],["mediawiki.Title","1450673896",["jquery.byteLength","mediawiki.util"]],["mediawiki.toc","1452703212",["jquery.cookie"]],["mediawiki.Uri","1450673896"],["mediawiki.user","1450673896",["jquery.cookie","mediawiki.api","user.options","user.tokens"]],["mediawiki.util","1450673896",["jquery.client","jquery.mwExtension","mediawiki.notify","mediawiki.toc"]],["mediawiki.action.edit","1450673896",["jquery.byteLimit","jquery.textSelection","mediawiki.action.edit.styles"]],["mediawiki.action.edit.styles","1450673896"],["mediawiki.action.edit.collapsibleFooter","1450673896",["jquery.cookie","jquery.makeCollapsible","mediawiki.icon"]],["mediawiki.action.edit.preview","1450673896",["jquery.form","jquery.spinner","mediawiki.action.history.diff"]],["mediawiki.action.history","1450673896",[],"mediawiki.action.history"],["mediawiki.action.history.diff","1450673896",[],"mediawiki.action.history"],["mediawiki.action.view.dblClickEdit","1450673896",["mediawiki.page.startup",
"mediawiki.util"]],["mediawiki.action.view.metadata","1452703328"],["mediawiki.action.view.postEdit","1452703212",["jquery.cookie","mediawiki.jqueryMsg"]],["mediawiki.action.view.redirectToFragment","1450673896",["jquery.client"]],["mediawiki.action.view.rightClickEdit","1450673896"],["mediawiki.action.edit.editWarning","1452707062",["mediawiki.jqueryMsg"]],["mediawiki.action.watch.ajax","1450065524",["mediawiki.page.watch.ajax"]],["mediawiki.language","1450673896",["mediawiki.cldr","mediawiki.language.data"]],["mediawiki.cldr","1450673896",["mediawiki.libs.pluralruleparser"]],["mediawiki.libs.pluralruleparser","1450673896"],["mediawiki.language.init","1450673896"],["mediawiki.jqueryMsg","1450673896",["mediawiki.language","mediawiki.util"]],["mediawiki.language.months","1452703224",["mediawiki.language"]],["mediawiki.libs.jpegmeta","1450673896"],["mediawiki.page.gallery","1450673896"],["mediawiki.page.ready","1450673896",["jquery.checkboxShiftClick","jquery.makeCollapsible",
"jquery.mw-jump","jquery.placeholder","mediawiki.util"]],["mediawiki.page.startup","1450673896",["mediawiki.util"]],["mediawiki.page.patrol.ajax","1452791638",["jquery.spinner","mediawiki.Title","mediawiki.api","mediawiki.notify","mediawiki.page.startup","mediawiki.util","user.tokens"]],["mediawiki.page.watch.ajax","1452704260",["jquery.mwExtension","mediawiki.api.watch","mediawiki.notify","mediawiki.page.startup","mediawiki.util"]],["mediawiki.page.image.pagination","1450673896",["jquery.spinner","mediawiki.Uri","mediawiki.util"]],["mediawiki.special","1450673896"],["mediawiki.special.block","1450673896",["mediawiki.util"]],["mediawiki.special.changeemail","1450673896",["mediawiki.util"]],["mediawiki.special.changeslist","1450673896"],["mediawiki.special.changeslist.legend","1450673896"],["mediawiki.special.changeslist.legend.js","1450673896",["jquery.cookie","jquery.makeCollapsible"]],["mediawiki.special.changeslist.enhanced","1450673896"],["mediawiki.special.movePage","1450673896",[
"jquery.byteLimit"]],["mediawiki.special.pagesWithProp","1450673896"],["mediawiki.special.preferences","1452725723",["mediawiki.language"]],["mediawiki.special.recentchanges","1450673896",["mediawiki.special"]],["mediawiki.special.search","1452703396"],["mediawiki.special.undelete","1450673896"],["mediawiki.special.upload","1452711446",["mediawiki.libs.jpegmeta","mediawiki.util"]],["mediawiki.special.userlogin.common.styles","1450673896"],["mediawiki.special.userlogin.signup.styles","1450673896"],["mediawiki.special.userlogin.login.styles","1450673896"],["mediawiki.special.userlogin.common.js","1452707054"],["mediawiki.special.userlogin.signup.js","1450673897",["jquery.throttle-debounce","mediawiki.api","mediawiki.jqueryMsg"]],["mediawiki.special.javaScriptTest","1450673897",["mediawiki.Uri"]],["mediawiki.special.version","1450673897"],["mediawiki.legacy.ajax","1450673897",["mediawiki.legacy.wikibits","mediawiki.util"]],["mediawiki.legacy.commonPrint","1450673895"],[
"mediawiki.legacy.config","1450673897",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.protect","1450673897",["jquery.byteLimit"]],["mediawiki.legacy.shared","1450673895"],["mediawiki.legacy.oldshared","1450673897"],["mediawiki.legacy.upload","1450673897",["jquery.spinner","mediawiki.Title","mediawiki.api","mediawiki.util"]],["mediawiki.legacy.wikibits","1450673897",["mediawiki.util"]],["mediawiki.ui","1450673897"],["mediawiki.ui.button","1450673895"],["oojs","1450673897"],["oojs-ui","1450673897",["oojs"]],["ext.categoryTree","1452703244"],["ext.categoryTree.css","1450673897"],["ext.confirmAccount","1450673897"],["ext.languageSelector","1450673897"],["ext.headertabs","1450673897",["jquery.ui.tabs"]]]);mw.config.set({"wgLoadScript":"/load.php","debug":false,"skin":"vector","stylepath":"/skins","wgUrlProtocols":
"http\\:\\/\\/|https\\:\\/\\/|ftp\\:\\/\\/|ftps\\:\\/\\/|ssh\\:\\/\\/|sftp\\:\\/\\/|irc\\:\\/\\/|ircs\\:\\/\\/|xmpp\\:|sip\\:|sips\\:|gopher\\:\\/\\/|telnet\\:\\/\\/|nntp\\:\\/\\/|worldwind\\:\\/\\/|mailto\\:|tel\\:|sms\\:|news\\:|svn\\:\\/\\/|git\\:\\/\\/|mms\\:\\/\\/|bitcoin\\:|magnet\\:|urn\\:|geo\\:|\\/\\/","wgArticlePath":"/index.php/$1","wgScriptPath":"","wgScriptExtension":".php","wgScript":"/index.php","wgSearchType":null,"wgVariantArticlePath":false,"wgActionPaths":{},"wgServer":"https://www.owasp.org","wgUserLanguage":"en","wgContentLanguage":"en","wgVersion":"1.23.12","wgEnableAPI":true,"wgEnableWriteAPI":true,"wgMainPageTitle":"Main Page","wgFormattedNamespaces":{"-2":"Media","-1":"Special","0":"","1":"Talk","2":"User","3":"User talk","4":"OWASP","5":"OWASP talk","6":"File","7":"File talk","8":"MediaWiki","9":"MediaWiki talk","10":"Template","11":"Template talk","12":"Help","13":"Help talk","14":"Category","15":"Category talk","274":"Widget","275":"Widget talk"},
"wgNamespaceIds":{"media":-2,"special":-1,"":0,"talk":1,"user":2,"user_talk":3,"owasp":4,"owasp_talk":5,"file":6,"file_talk":7,"mediawiki":8,"mediawiki_talk":9,"template":10,"template_talk":11,"help":12,"help_talk":13,"category":14,"category_talk":15,"widget":274,"widget_talk":275,"image":6,"image_talk":7,"project":4,"project_talk":5},"wgContentNamespaces":[0],"wgSiteName":"OWASP","wgFileExtensions":["vsd","odp","gif","png","jpg","jpeg","doc","ppt","mp3","pdf","psd","zip","tar","tar.gz","tar.bz2","jar","docx","pptx","xls","xlsx"],"wgDBname":"wiki","wgFileCanRotate":true,"wgAvailableSkins":{"vector":"Vector","cologneblue":"CologneBlue","modern":"Modern","monobook":"MonoBook"},"wgExtensionAssetsPath":"/extensions","wgCookiePrefix":"wiki","wgResourceLoaderMaxQueryLength":-1,"wgCaseSensitiveNamespaces":[],"wgLegalTitleChars":" %!\"$\u0026'()*,\\-./0-9:;=?@A-Z\\\\\\^_`a-z~+\\u0080-\\uFFFF","wgResourceLoaderStorageVersion":1,"wgResourceLoaderStorageEnabled":false,"htUseHistory":true,
"htEditTabLink":true});};if(isCompatible()){document.write("\u003Cscript src=\"/load.php?debug=false\u0026amp;lang=en\u0026amp;modules=jquery%2Cmediawiki\u0026amp;only=scripts\u0026amp;skin=vector\u0026amp;version=20151221T045816Z\"\u003E\u003C/script\u003E");};
/* cache key: wiki:resourceloader:filter:minify-js:7:671eac7be1229e78e4ab3f059faea091 */