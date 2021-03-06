// This file is part of Ambulant Player, www.ambulantplayer.org.
//
// Copyright (C) 2003-2015 Stichting CWI, 
// Science Park 123, 1098 XG Amsterdam, The Netherlands.
//
// Ambulant Player is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// Ambulant Player is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Ambulant Player; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#import "AmbulantWebViewController.h"


@implementation AmbulantWebViewController

-(void) loadURL {
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	NSString* urlstring;

	NSURL* url;
	if (urlField == nil) {
		NSBundle* thisBundle = [NSBundle bundleForClass:[self class]];
		urlstring = [thisBundle pathForResource:@"AmbulantHelp-iOS" ofType:@"html"];
		url = [[NSURL alloc] initFileURLWithPath: urlstring];
	} else {
		urlstring = [NSString stringWithString: urlField];
		url = [[NSURL alloc] initWithString: urlstring];
	}
	NSURLRequest *request = [[NSURLRequest alloc] initWithURL: url];
	[webView loadRequest: request]; 
	[pool release];
}

- (void)viewDidLoad {
	NSLog(@"AmbulantWebViewController: viewDidLoad");
    [super viewDidLoad];
	webView.scalesPageToFit = YES;
	[self loadURL];
}

- (IBAction) handleBackTapped {
	if (webView.canGoBack) {
		[webView goBack];
	} else {
		[delegate auxViewControllerDidFinish:self];
	}
}

- (IBAction) handleDoneTapped {
	[delegate auxViewControllerDidFinish: self];
//	[self dismissModalViewControllerAnimated:YES];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    return [delegate canShowRotatedUIViews];
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}


@end
